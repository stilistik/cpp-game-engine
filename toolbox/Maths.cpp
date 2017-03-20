/*
 * Maths.cpp
 *
 *  Created on: 06.11.2016
 *      Author: Philipp
 */

#include "Maths.h"

const double Maths::PI = 3.1415926535897;

glm::mat4 Maths::createTransformationMatrix(const glm::vec3 translation, const float rx, const float ry, const float rz, const float scale){
	glm::mat4 matrix = glm::translate(glm::mat4(1.0), translation);
	matrix = glm::rotate(matrix, rx, glm::vec3(1,0,0));
	matrix = glm::rotate(matrix, ry, glm::vec3(0,1,0));
	matrix = glm::rotate(matrix, rz, glm::vec3(0,0,1));
	matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
	return matrix;
}

glm::mat4 Maths::createViewMatrix(const Camera& camera){
	glm::mat4 viewMatrix = glm::mat4(1.0);
	viewMatrix = glm::rotate(viewMatrix, toRadians(camera.getPitch()), glm::vec3(1,0,0));
	viewMatrix = glm::rotate(viewMatrix, toRadians(camera.getYaw()), glm::vec3(0,1,0));
	glm::vec3 cameraPos = camera.getPosition();
	glm::vec3 negativeCameraPos = glm::vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z);
	viewMatrix = glm::translate(viewMatrix, negativeCameraPos);
	return viewMatrix;
}

float Maths::toRadians(const float angle){
	double halfC = PI / 180;
	return angle * halfC;
}

float Maths::toDegrees(const float rad){
	double halfC = PI / 180;
	return rad / halfC;
}
