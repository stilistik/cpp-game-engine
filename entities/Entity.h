/*
 * Entity.h
 *
 *  Created on: 06.11.2016
 *      Author: Philipp
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <glm/glm.hpp>
#include "../models/TexturedModel.h"

class Entity {
protected:

	TexturedModel model;
	glm::vec3 position;
	float rotX, rotY, rotZ;
	float scale;

public:

	Entity(TexturedModel m, glm::vec3 pos, float rx, float ry, float rz, float s);

	void increasePosition(float dx, float dy, float dz);
	void increaseRotation(float dx, float dy, float dz);

	const TexturedModel& getModel() const { return model; }
	void setModel(const TexturedModel& model) {	this->model = model; }
	const glm::vec3& getPosition() const { return position; }
	void setPosition(const glm::vec3& position) { this->position = position; }
	float getRotX() const {	return rotX; }
	void setRotX(float rotX) { this->rotX = rotX; }
	float getRotY() const {	return rotY; }
	void setRotY(float rotY) { this->rotY = rotY; }
	float getRotZ() const {	return rotZ; }
	void setRotZ(float rotZ) { this->rotZ = rotZ; }
	float getScale() const { return scale; }
	void setScale(float scale) { this->scale = scale; }
};

#endif /* ENTITY_H_ */
