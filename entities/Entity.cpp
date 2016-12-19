/*
 * Entity.cpp
 *
 *  Created on: 06.11.2016
 *      Author: Philipp
 */

#include "Entity.h"

Entity::Entity(TexturedModel m, glm::vec3 pos, float rx, float ry, float rz, float s)
	: model{m}, position{pos}, rotX{rx}, rotY{ry}, rotZ{rz}, scale{s} {}

void Entity::increasePosition(float dx, float dy, float dz){
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz){
	rotX += dx;
	rotY += dy;
	rotZ += dz;
}

