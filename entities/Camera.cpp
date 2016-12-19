/*
 * Camera.cpp
 *
 *  Created on: 06.11.2016
 *      Author: Philipp
 */

#include "Camera.h"
#include <cmath>

Camera::Camera(PlayerPointer p) : player{p}, position{player->getPosition()}, pitch{0}, yaw{0}, roll{0} {
	setKeyHandling();
	setMouseHandling();
	setScrollHandling();
	setCursorHandling();
}

void Camera::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_W && action == GLFW_PRESS){
		if (std::abs(angleAroundPlayer) > 0){
			resetAngle = true;
		}
	}
}


void Camera::mouseCallback(GLFWwindow* window, int button, int action, int mods){
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS){
		button1_pressed = true;
	}

	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE){
		button1_pressed = false;
	}
}

void Camera::scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
	if (yoffset != 0){
		distanceFromPlayer -= yoffset*0.1f;
	}
}

void Camera::cursorCallback(GLFWwindow* window, double xpos, double ypos){
	if (button1_pressed){
		double dx = xpos - xpos_old;
		double dy = ypos - ypos_old;
		if (std::abs(dx) > maxCamVelocity)
			dx = 0;
		if (std::abs(dy) > maxCamVelocity)
			dy = 0;
		xpos_old = xpos;
		ypos_old = ypos;
		pitch += dy * 0.1f;
		angleAroundPlayer -= dx * 0.1f;
	}
}

void Camera::move(){
	if (resetAngle){
		angleAroundPlayer > 0 ? (angleAroundPlayer-=resetSpeed) : (angleAroundPlayer+=resetSpeed);
		if (std::abs(angleAroundPlayer) < 1){
			angleAroundPlayer = 0;
			resetAngle = false;
		}
	}
	float horizontalDistance = distanceFromPlayer * std::cos(Maths::toRadians(pitch));
	float verticalDistance = distanceFromPlayer * std::sin(Maths::toRadians(pitch));
	float theta = player->getRotY() + Maths::toRadians(angleAroundPlayer);
	float xOffset = horizontalDistance * std::sin(theta);
	float zOffset = horizontalDistance * std::cos(theta);
	position.x = player->getPosition().x + xOffset;
	position.y = player->getPosition().y + verticalDistance;
	position.z = player->getPosition().z + zOffset;
	yaw = 360 - (Maths::toDegrees(player->getRotY()) + angleAroundPlayer);
}
