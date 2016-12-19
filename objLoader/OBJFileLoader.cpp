/*
 * OBJLoader.cpp
 *
 *  Created on: 06.11.2016
 *      Author: Philipp
 */

#include "ObjFileLoader.h"

ModelData OBJFileLoader::loadObjModel(const char* fileName, Loader& loader){

	FILE * file = fopen(fileName, "r");
	if( file == NULL ){
		std::cerr << "OBJLoader: Error opening obj-file." << std::endl;
	}

	std::vector<VertexPointer> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<int> indicesArray;

	std::vector<float> verticesArray;
	std::vector<float> texturesArray;
	std::vector<float> normalsArray;

	while(true) {
	    char lineHeader[128];
	    int res = fscanf(file, "%s", lineHeader);
	    if (res == EOF){
	        break;
	    }
	    if (strcmp(lineHeader, "v") == 0){
	        glm::vec3 v;
	        fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z );
	        vertices.push_back(VertexPointer(new Vertex(v, vertices.size())));
	    }else if (strcmp(lineHeader, "vt") == 0){
	    	glm::vec2 texture;
	    	fscanf(file, "%f %f\n", &texture.x, &texture.y);
	    	textures.push_back(texture);
	    }else if (strcmp(lineHeader, "vn") == 0){
	    	glm::vec3 normal;
	    	fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
	    	normals.push_back(normal);
	    }else if (strcmp(lineHeader, "f") == 0){
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

	verticesArray = std::vector<float>(vertices.size()*3);
	texturesArray = std::vector<float>(vertices.size()*2);
	normalsArray = std::vector<float>(vertices.size()*3);

	removeUnusedVertices(vertices);

	float furthest = convertData(vertices, textures, normals, verticesArray, texturesArray, normalsArray);

	return ModelData(verticesArray, texturesArray, normalsArray, indicesArray, furthest);
}

void OBJFileLoader::processVertex(std::vector<int>& vertexData, std::vector<VertexPointer>& vertices, std::vector<int>& indices){
	int index = vertexData[0]-1;
	int texIndex = vertexData[1]-1;
	int norIndex = vertexData[2]-1;
	VertexPointer currentVertex = VertexPointer(vertices[index]);
	if (!currentVertex->isSet()){
		currentVertex->setTextureIndex(texIndex);
		currentVertex->setNormalIndex(norIndex);
		indices.push_back(index);
	}else{
		dealWithProcessedVertex(currentVertex, texIndex, norIndex, indices, vertices);
	}
}

 void OBJFileLoader::dealWithProcessedVertex(VertexPointer previousVertex, int n_texIndex, int n_norIndex, std::vector<int>& indices, std::vector<VertexPointer>& vertices){
	 if(previousVertex->hasSameTexNor(n_texIndex, n_norIndex)){
		 indices.push_back(previousVertex->getIndex());
	 }else{
		 if(previousVertex->hasDuplicateVertex()){
			 VertexPointer anotherVertex = previousVertex->getDuplicateVertex();
			 dealWithProcessedVertex(anotherVertex, n_texIndex, n_norIndex, indices, vertices);
		 }else{
			 VertexPointer duplicateVertex = VertexPointer(new Vertex(previousVertex->getPosition(), vertices.size()));
             duplicateVertex->setTextureIndex(n_texIndex);
             duplicateVertex->setNormalIndex(n_norIndex);
             previousVertex->setDuplicateVertex(duplicateVertex);
             vertices.push_back(duplicateVertex);
             indices.push_back(duplicateVertex->getIndex());
		 }
	 }
 }

void OBJFileLoader::removeUnusedVertices(std::vector<VertexPointer>& vertices){
	for(VertexPointer v : vertices){
		if(!v->isSet()){
			v->setTextureIndex(0);
			v->setNormalIndex(0);
		}
	}
}

float OBJFileLoader::convertData(std::vector<VertexPointer>& vertices, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals,
								 std::vector<float>& verticesArray, std::vector<float>& texturesArray, std::vector<float>& normalsArray){
    float furthestPoint = 0;
    for (unsigned int i = 0; i < vertices.size(); i++) {
    	VertexPointer currentVertex = vertices[i];
        if (currentVertex->getLength() > furthestPoint) {
            furthestPoint = currentVertex->getLength();
        }
        glm::vec3 position = currentVertex->getPosition();
        glm::vec2 textureCoord = textures[currentVertex->getTextureIndex()];
        glm::vec3 normalVector = normals[currentVertex->getNormalIndex()];
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





