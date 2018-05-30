/*
 * Loader.cpp
 *
 *  Created on: 04.11.2016
 *      Author: Philipp Gerber
 */

#include "Loader.h"
#include <iostream>

/*
 * Main method of this class. This creates a VAO for our model and a VBO for each of the supplied data containers (vertices,
 * texture coordinates, normals) as well as an index buffer. The VBOs are attached to the VAO and the VAO id is stored in the RawModel, which
 * is then returned.
 */
RawModel Loader::loadToVAO(const std::vector<float>& ver, const std::vector<float>& tex, const std::vector<float>& nor, const std::vector<int>& ind){
	int indexCount = ind.size();
	int vertexCount = ver.size()/3; // a vertex is 3 consecutive elements
	int normalsCount = nor.size()/3;
	GLuint vaoID = createVAO();
	bindIndicesBuffer(ind, indexCount);
	storeDataInAttributeList(0, 3, ver, vertexCount);
	storeDataInAttributeList(1, 2, tex, vertexCount);
	storeDataInAttributeList(2, 3, nor, normalsCount);
	unbindVAO();
	return RawModel(vaoID, indexCount);
}

/*
 * This loads an image into an OpenGL texture object.
 */
GLuint Loader::loadTexture(const char* file){
	// load image
	int width, height, channels;
	unsigned char* image = SOIL_load_image(file, &width, &height, &channels, SOIL_LOAD_AUTO);

	// generate texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	textures.push_back(textureID); // keep track of textures
	glBindTexture(GL_TEXTURE_2D, textureID);

	// check transparency
	if (channels == 4){
		// load rgba image to texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	}else{
		// load rgb image to texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}

	SOIL_free_image_data(image);

	// enable texture interpolation
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// enable mip mapping
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4);
	return textureID;
}


/*
 * Helper method to create an empty VAO
 */
GLuint Loader::createVAO(){
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	vaos.push_back(vao); // keep track of vaos
	return vao;
}

/*
 * Helper method to unbind the currently bound VAO if there is any.
 */
void Loader::unbindVAO(){
	glBindVertexArray(0);
}

/*
 * This creates a VBO for an attribute (such as normal vectors, texture coordinates, etc.) and stores the attribute data in
 * the VBO.
 */
void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, const std::vector<float>& data, int vertexCount){
	GLuint vbo;
	glGenBuffers(1, &vbo);
	vbos.push_back(vbo); // keep track of vbos
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// store the data in the VBO for static draw
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*coordinateSize*vertexCount, &data[0], GL_STATIC_DRAW);

	// attach the vbo to the currently bound VAO
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
}

/*
 * This creates a VBO for the index buffer. This has to be an element array buffer instead of a conventional array buffer.
 */
void Loader::bindIndicesBuffer(const std::vector<int>& indices, int vertexCount){
	GLuint vbo;
	glGenBuffers(1, &vbo);
	vbos.push_back(vbo); // keep track of vbos
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT)*vertexCount, &indices[0], GL_STATIC_DRAW);
}

/*
 * This makes sure all the OpenGL objects are destroyed when the program exits.
 */
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

