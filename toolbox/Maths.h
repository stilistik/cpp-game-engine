/*
 * Maths.h
 *
 *  Created on: 06.11.2016
 *      Author: Philipp
 */

#ifndef MATHS_H_
#define MATHS_H_

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../entities/Camera.h"

class Camera;

class Maths {
public:

	static const double PI;

	static glm::mat4 createTransformationMatrix(const glm::vec3 translation, const float rx, const float ry, const float rz, const float scale);
	static glm::mat4 createViewMatrix(const Camera& camera);
	static float toRadians(const float angle);
	static float toDegrees(const float rad);

};

#endif /* MATHS_H_ */
