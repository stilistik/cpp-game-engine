/*
 * Vertex.cpp
 *
 *  Created on: 09.11.2016
 *      Author: Philipp Gerber
 */

#include "Vertex.h"
#include <glm/glm.hpp>


const int Vertex::NO_INDEX = -1;

Vertex::Vertex(const glm::vec3& p, int i) : position{p}, index{i}  {
	length = glm::length(p);
	normalIndex = NO_INDEX;
	textureIndex = NO_INDEX;
	duplicateVertex = nullptr;
	duplicateFlag = false;
}

/*
 * This method returns true when this vertex has a normal vector and a texture coordinate assigned.
 */
bool Vertex::isSet(){
	return textureIndex!=NO_INDEX && normalIndex!=NO_INDEX;
}

/*
 * This method compares 2 vertices with respect to their texture coordinates and normal vector indices
 */
bool Vertex::hasSameTexNor(int ti_other, int ni_other){
	return textureIndex==ti_other && normalIndex==ni_other;
}
