/*
 * RawModel.h
 *
 *  Created on: 04.11.2016
 *      Author: Philipp Gerber
 *
 *  The RawModel class represents an OpenGL VAO object. A VAO is an object in the graphics context containing vertex data, normals,
 *  indices and texture coordinates for a model.
 */

#ifndef RAWMODEL_H_
#define RAWMODEL_H_

#include <GL/glew.h>

class RawModel {
private:

	GLuint vaoID;
	int vertexCount;

public:

	// ctor
	RawModel();
	RawModel(GLuint id, int vc);

	// getter
	GLuint getVaoID();
	int getVertexCount();
};

#endif /* RAWMODEL_H_ */
