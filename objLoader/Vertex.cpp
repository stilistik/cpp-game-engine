/*
 * Vertex.cpp
 *
 *  Created on: 09.11.2016
 *      Author: Philipp
 */

#include "Vertex.h"

const int Vertex::NO_INDEX = -1;

Vertex::Vertex(const glm::vec3& p, int i) : position{p}, index{i}  {
	length = p.length();
	normalIndex = NO_INDEX;
	textureIndex = NO_INDEX;
	duplicateVertex = nullptr;
	duplicateFlag = false;
}

bool Vertex::isSet(){
	return textureIndex!=NO_INDEX && normalIndex!=NO_INDEX;
}

bool Vertex::hasSameTexNor(int ti_other, int ni_other){
	return textureIndex==ti_other && normalIndex==ni_other;
}
