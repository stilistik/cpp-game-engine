/*
 * Loader.h
 *
 *  Created on: 04.11.2016
 *      Author: Philipp Gerber
 *
 * The loader class has the purpose of populating OpenGL data structures with model data. The vertices, normals and texture
 * coordinates of our models are loaded into VAOs and VBOs, which can then be bound by OpenGL for rendering.
 */

#ifndef LOADER_H_
#define LOADER_H_

#include <GL/glew.h>
#include <vector>
#include "../models/RawModel.h"
#include <SOIL/SOIL.h>


class Loader {
private:

	// loader keeps track of created buffers and objects
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	std::vector<GLuint> textures;


	GLuint createVAO();
	void unbindVAO();
	void storeDataInAttributeList(int attributeNumber, int coordinateSize, const std::vector<float>& data, int vertexCount);
	void bindIndicesBuffer(const std::vector<int>& data, int vertexCount);

public:

	RawModel loadToVAO(const std::vector<float>& ver, const std::vector<float>& tex, const std::vector<float>& nor, const std::vector<int>& ind);
	GLuint loadTexture(const char* file);
	void cleanUp();

};

#endif /* LOADER_H_ */
