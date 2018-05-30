/*
 * Camera.cpp
 *
 *  Created on: 06.11.2016
 *      Author: Philipp Gerber
 */

#include "Camera.h"
#include <cmath>

/*
 * ctor: declare the camera a handling instance for CallbackBase
 */
Camera::Camera(Player* p) : player{p}, position{player->getPosition()}, pitch{0}, yaw{0}, roll{0} {
	setKeyHandling();
	setMouseHandling();
	setScrollHandling();
	setCursorHandling();
}

/*
 * KeyCallback method is called by the Callback dispatcher of CallbackBase. If the W-key is pressed, the player
 * moves forward and we want to reset the camera behind the player in this case.
 */
void Camera::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_W && action == GLFW_PRESS){
		if (std::abs(angleAroundPlayer) > 0){
			resetAngle = true;
		}
	}
}

/*
 * MouseCallback method is called by the Callback dispatcher of CallbackBase. This method sets the pressed state for
 * the left mouse button.
 */
void Camera::mouseCallback(GLFWwindow* window, int button, int action, int mods){
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS){
		button1_pressed = true;
	}

	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE){
		button1_pressed = false;
	}
}

/*
 * This method handles zooming of the camera, i.e. the distance of the camera to the player. Called by the CallbackBase dispatcher
 * function.
 */
void Camera::scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
	if (yoffset != 0){
		distanceFromPlayer -= yoffset;
	}
}

/*
 * This callback method is called by the CallbackBase dispatcher function whenever the cursor is moved by the user. Only
 * if the left mouse button is pressed, we want to change the cameras position relative to the player.
 */
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

/*
 * This is the main update method for the camera object that is called during each iteration of the main render loop.
 */
void Camera::move(){
	if (resetAngle){
		// we want to reposition the camera behind the player, since player is moving
		angleAroundPlayer > 0 ? (angleAroundPlayer-=resetSpeed) : (angleAroundPlayer+=resetSpeed);
		if (std::abs(angleAroundPlayer) < 1){
			// camera is centered behind player
			angleAroundPlayer = 0;
			resetAngle = false;
		}
	}
	// update all the camera parameters. The view matrix is computed from these parameters during the rendering procedure.
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
