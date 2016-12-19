/*
 * RawModel.h
 *
 *  Created on: 04.11.2016
 *      Author: Philipp
 */

#ifndef RAWMODEL_H_
#define RAWMODEL_H_

#include <GL/glew.h>

class RawModel {
private:

	GLuint vaoID;
	int vertexCount;

public:

	RawModel();
	RawModel(GLuint id, int vc);
	GLuint getVaoID();
	int getVertexCount();
};

#endif /* RAWMODEL_H_ */
