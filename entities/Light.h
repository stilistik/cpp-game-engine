/*
 * Light.h
 *
 *  Created on: 07.11.2016
 *      Author: Philipp
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <glm/glm.hpp>

class Light {
private:

	glm::vec3 position;
	glm::vec3 color;

public:

	Light(glm::vec3 p, glm::vec3 c);
	const glm::vec3& getColor() const { return color; }
	void setColor(const glm::vec3& c) {	color = c; }
	const glm::vec3& getPosition() const { return position; }
	void setPosition(const glm::vec3& p) { position = p; }

};

#endif /* LIGHT_H_ */
