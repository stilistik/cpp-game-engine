/*
 * OBJLoader.cpp
 *
 *  Created on: 06.11.2016
 *      Author: Philipp
 */

#include "OBJLoader.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <glm/glm.hpp>

RawModel OBJLoader::loadObjModel(const char* fileName, Loader& loader){
	FILE * file = fopen(fileName, "r");
	if( file == NULL ){
		std::cerr << "OBJLoader: Error opening obj-file." << std::endl;
	}

	bool initialize = true;

	std::vector<glm::vec3> vertices;
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
	        glm::vec3 vertex;
	        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
	        vertices.push_back(vertex);
	    }else if (strcmp(lineHeader, "vt") == 0){
	    	glm::vec2 texture;
	    	fscanf(file, "%f %f\n", &texture.x, &texture.y);
	    	textures.push_back(texture);
	    }else if (strcmp(lineHeader, "vn") == 0){
	    	glm::vec3 normal;
	    	fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
	    	normals.push_back(normal);
	    }else if (strcmp(lineHeader, "f") == 0){
	    	if (initialize){
	    		texturesArray = std::vector<float>(vertices.size()*2);
	    		normalsArray = std::vector<float>(vertices.size()*3);
	    		initialize = false;
	    	}
	    	std::vector<int> vertex_1(3);
	    	std::vector<int> vertex_2(3);
	    	std::vector<int> vertex_3(3);
	    	fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_1[0], &vertex_1[1], &vertex_1[2], &vertex_2[0], &vertex_2[1], &vertex_2[2], &vertex_3[0], &vertex_3[1], &vertex_3[2]);
	    	processVertex(vertex_1, indicesArray, textures, normals, texturesArray, normalsArray);
	    	processVertex(vertex_2, indicesArray, textures, normals, texturesArray, normalsArray);
	    	processVertex(vertex_3, indicesArray, textures, normals, texturesArray, normalsArray);
	    }
	}
	for (glm::vec3 v : vertices){
		verticesArray.push_back(v.x);
		verticesArray.push_back(v.y);
		verticesArray.push_back(v.z);
	}
	return loader.loadToVAO(verticesArray, texturesArray, normalsArray, indicesArray);
}

void OBJLoader::processVertex(std::vector<int>& vertexData, std::vector<int>& indices,
		std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals,
		std::vector<float>& texturesArray, std::vector<float>& normalsArray){

	int currentVertexPointer = vertexData[0] - 1;
	indices.push_back(currentVertexPointer);
	glm::vec2 currentTex = textures[vertexData[1]-1];
	texturesArray[currentVertexPointer*2] = currentTex.x;
	texturesArray[currentVertexPointer*2+1] = 1 - currentTex.y;
	glm::vec3 currentNorm = normals[vertexData[2]-1];
	normalsArray[currentVertexPointer*3] = currentNorm.x;
	normalsArray[currentVertexPointer*3+1] = currentNorm.y;
	normalsArray[currentVertexPointer*3+2] = currentNorm.z;
}


