/*
 * RawModel.cpp
 *
 *  Created on: 04.11.2016
 *      Author: Philipp
 */

#include "RawModel.h"

RawModel::RawModel(){
	vaoID = 0;
	vertexCount = 0;
}

RawModel::RawModel(GLuint id, int vc) : vaoID{id}, vertexCount{vc} {}

GLuint RawModel::getVaoID(){
	return vaoID;
}

int RawModel::getVertexCount(){
	return vertexCount;
}
