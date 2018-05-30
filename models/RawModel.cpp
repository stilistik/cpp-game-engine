/*
 * RawModel.cpp
 *
 *  Created on: 04.11.2016
 *      Author: Philipp Gerber
 */

#include "RawModel.h"


/*
 * default ctor
 */
RawModel::RawModel(){
	vaoID = 0;
	vertexCount = 0;
}

/*
 * ctor
 */
RawModel::RawModel(GLuint id, int vc) : vaoID{id}, vertexCount{vc} {}


/*
 * Returns the ID of the VAO that represents this model in the graphics memory
 */
GLuint RawModel::getVaoID(){
	return vaoID;
}

/*
 * Returns the number of vertices that are part of this model
 */
int RawModel::getVertexCount(){
	return vertexCount;
}
