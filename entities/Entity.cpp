/*
 * Entity.cpp
 *
 *  Created on: 06.11.2016
 *      Author: Philipp Gerber
 */

#include "Entity.h"
#include <glm/glm.hpp>


Entity::Entity(TexturedModel m, glm::vec3 pos, float rx, float ry, float rz, float s)
	: model{m}, position{pos}, rotX{rx}, rotY{ry}, rotZ{rz}, scale{s} {}


/*
 * This method is used to move an entity around in the scene at runtime
 */
void Entity::increasePosition(float dx, float dy, float dz){
	position.x += dx;
	position.y += dy;
	position.z += dz;
}


/*
 * This method is used to rotate an entity in the scene at runtime
 */
void Entity::increaseRotation(float dx, float dy, float dz){
	rotX += dx;
	rotY += dy;
	rotZ += dz;
}

