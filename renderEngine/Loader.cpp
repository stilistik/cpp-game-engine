/*
 * Loader.cpp
 *
 *  Created on: 04.11.2016
 *      Author: Philipp
 */

#include "Loader.h"
#include <iostream>

RawModel Loader::loadToVAO(const std::vector<float>& ver, const std::vector<float>& tex, const std::vector<float>& nor, const std::vector<int>& ind){
	int indexCount = ind.size();
	int vertexCount = ver.size()/3;
	int normalsCount = nor.size()/3;
	GLuint vaoID = createVAO();
	bindIndicesBuffer(ind, indexCount);
	storeDataInAttributeList(0, 3, ver, vertexCount);
	storeDataInAttributeList(1, 2, tex, vertexCount);
	storeDataInAttributeList(2, 3, nor, normalsCount);
	unbindVAO();
	return RawModel(vaoID, indexCount);
}

GLuint Loader::loadTexture(const char* file){
	int width, height, channels;
	unsigned char* image = SOIL_load_image(file, &width, &height, &channels, SOIL_LOAD_AUTO);
	GLuint textureID;
	glGenTextures(1, &textureID);
	textures.push_back(textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	if (channels == 4){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	}else{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4);
	return textureID;
}

GLuint Loader::createVAO(){
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	vaos.push_back(vao);
	return vao;
}

void Loader::unbindVAO(){
	glBindVertexArray(0);
}

void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, const std::vector<float>& data, int vertexCount){
	GLuint vbo;
	glGenBuffers(1, &vbo);
	vbos.push_back(vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*coordinateSize*vertexCount, &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
}

void Loader::bindIndicesBuffer(const std::vector<int>& indices, int vertexCount){
	GLuint vbo;
	glGenBuffers(1, &vbo);
	vbos.push_back(vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT)*vertexCount, &indices[0], GL_STATIC_DRAW);
}

void Loader::cleanUp(){
	for (GLuint vao : vaos){
		glDeleteVertexArrays(1, &vao);
	}
	for (GLuint vbo : vbos){
		glDeleteBuffers(1, &vbo);
	}
	for (GLuint tex : textures){
		glDeleteTextures(1, &tex);
	}
}

