/*
 * OBJLoader.cpp
 *
 *  Created on: 06.11.2016
 *      Author: Philipp Gerber
 */

#include "OBJFileLoader.h"
#include <glm/glm.hpp>

/*
 * Main method of this class.
 */
ModelData OBJFileLoader::loadObjModel(const char* fileName, Loader& loader){

	// open file
	FILE * file = fopen(fileName, "r");
	if( file == NULL ){
		std::cerr << "OBJLoader: Error opening obj-file." << std::endl;
	}

	// containers for the read data
	std::vector<VertexPointer> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<int> indicesArray;

	std::vector<float> verticesArray;
	std::vector<float> texturesArray;
	std::vector<float> normalsArray;

	// loop over the lines of the file
	while(true) {
	    char lineHeader[128];
	    int res = fscanf(file, "%s", lineHeader); // read a line
	    if (res == EOF){
	    	// check for end of file
	        break;
	    }

	    if (strcmp(lineHeader, "v") == 0){
	    	// line represents vertex position data
	        glm::vec3 v;
	        fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z );
	        vertices.push_back(VertexPointer(new Vertex(v, vertices.size())));

	    }else if (strcmp(lineHeader, "vt") == 0){
	    	// line represents texture coordinate data
	    	glm::vec2 texture;
	    	fscanf(file, "%f %f\n", &texture.x, &texture.y);
	    	textures.push_back(texture);

	    }else if (strcmp(lineHeader, "vn") == 0){
	    	// line represents normal vector data
	    	glm::vec3 normal;
	    	fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
	    	normals.push_back(normal);

	    }else if (strcmp(lineHeader, "f") == 0){
	    	// line represents a face of 3 vertices. we have to create the index buffer from this information
	    	std::vector<int> vertex_1(3);
	    	std::vector<int> vertex_2(3);
	    	std::vector<int> vertex_3(3);
	    	fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_1[0], &vertex_1[1], &vertex_1[2], &vertex_2[0], &vertex_2[1], &vertex_2[2], &vertex_3[0], &vertex_3[1], &vertex_3[2]);
	    	processVertex(vertex_1, vertices, indicesArray);
	    	processVertex(vertex_2, vertices, indicesArray);
	    	processVertex(vertex_3, vertices, indicesArray);
	    }
	}

	fclose(file);

	// OpenGL needs the data element-wise. A 3d vector consists of 3 consecutive array elements.
	verticesArray = std::vector<float>(vertices.size()*3);
	texturesArray = std::vector<float>(vertices.size()*2);
	normalsArray = std::vector<float>(vertices.size()*3);

	removeUnusedVertices(vertices);

	float furthest = convertData(vertices, textures, normals, verticesArray, texturesArray, normalsArray);

	return ModelData(verticesArray, texturesArray, normalsArray, indicesArray, furthest);
}

/*
 * This method reads the vertex index, texture index and normal index from the face information contained in vertexData and
 * provides the Vertex objects in vertices with these indices. If they already have indices set, we have to check if the current
 * indices are the same as the ones that were previously set.
 */
void OBJFileLoader::processVertex(std::vector<int>& vertexData, std::vector<VertexPointer>& vertices, std::vector<int>& indices){
	int index = vertexData[0]-1;
	int texIndex = vertexData[1]-1;
	int norIndex = vertexData[2]-1;
	VertexPointer currentVertex = vertices[index];
	if (!currentVertex->isSet()){
		currentVertex->setTextureIndex(texIndex);
		currentVertex->setNormalIndex(norIndex);
		indices.push_back(index);
	}else{
		// current vertex already has texture index and normal index
		dealWithProcessedVertex(currentVertex, texIndex, norIndex, indices, vertices);
	}
}

 void OBJFileLoader::dealWithProcessedVertex(VertexPointer previousVertex, int n_texIndex, int n_norIndex, std::vector<int>& indices, std::vector<VertexPointer>& vertices){
	 // check if the vertex has the same indices set as the ones read from the face information
	 if(previousVertex->hasSameTexNor(n_texIndex, n_norIndex)){
		 indices.push_back(previousVertex->getIndex()); // if so, we can push the index of the vertex onto the index buffer
	 }else{
		 // we have different indices than the vertex has set
		 if(previousVertex->hasDuplicateVertex()){
			 // there is a duplicate vertex with the same position as previousVertex
			 VertexPointer anotherVertex = previousVertex->getDuplicateVertex();
			 // recursively call this method until all duplicates have been checked
			 dealWithProcessedVertex(anotherVertex, n_texIndex, n_norIndex, indices, vertices);
		 }else{
			 // there is no duplicate vertex yet, so we create one
			 VertexPointer duplicateVertex = VertexPointer(new Vertex(previousVertex->getPosition(), vertices.size()));

			 // set the indices of the newly created duplicate to the new indices
             duplicateVertex->setTextureIndex(n_texIndex);
             duplicateVertex->setNormalIndex(n_norIndex);

             // set the new vertex as duplicate of the previous vertex
             previousVertex->setDuplicateVertex(duplicateVertex);

             // push the stuff
             vertices.push_back(duplicateVertex);
             indices.push_back(duplicateVertex->getIndex());
		 }
	 }
 }

/*
 * This method removes unused vertices, i.e. vertices without normal and texture indices
 */
void OBJFileLoader::removeUnusedVertices(std::vector<VertexPointer>& vertices){
	for(VertexPointer v : vertices){
		if(!v->isSet()){
			v->setTextureIndex(0);
			v->setNormalIndex(0);
		}
	}
}

/*
 * This method restructures our arrays. In the input arrays, we have a vertex being represented by one element in the array.
 * However, OpenGL needs the data such that a vertex is represented by 3 consecutive elements in the array.
 */
float OBJFileLoader::convertData(std::vector<VertexPointer>& vertices, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals,
								 std::vector<float>& verticesArray, std::vector<float>& texturesArray, std::vector<float>& normalsArray){
    float furthestPoint = 0;
    for (unsigned int i = 0; i < vertices.size(); i++) {
    	VertexPointer currentVertex = vertices[i];
        if (currentVertex->getLength() > furthestPoint) {
            furthestPoint = currentVertex->getLength();
        }

        // get the data from the containers
        glm::vec3 position = currentVertex->getPosition();
        glm::vec2 textureCoord = textures[currentVertex->getTextureIndex()];
        glm::vec3 normalVector = normals[currentVertex->getNormalIndex()];

        // put into arrays
        verticesArray[i * 3] = position.x;
        verticesArray[i * 3 + 1] = position.y;
        verticesArray[i * 3 + 2] = position.z;
        texturesArray[i * 2] = textureCoord.x;
        texturesArray[i * 2 + 1] = 1 - textureCoord.y;
        normalsArray[i * 3] = normalVector.x;
        normalsArray[i * 3 + 1] = normalVector.y;
        normalsArray[i * 3 + 2] = normalVector.z;
    }
    return furthestPoint;
}





