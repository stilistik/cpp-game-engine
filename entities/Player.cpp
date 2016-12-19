/*
 * Player.cpp
 *
 *  Created on: 15.12.2016
 *      Author: Philipp
 */

#include "Player.h"

Player::Player(TexturedModel m, glm::vec3 pos, float rX, float rY, float rZ, float s)
	: Entity(m, pos, rX, rY, rZ, s) , currentSpeed{0}, currentTurnSpeed{0}, upwardsSpeed{0}, isInAir{false} {
		setKeyHandling();
	}

void Player::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	// key pressed
	if (key == GLFW_KEY_W && action == GLFW_PRESS){
		currentSpeed = -RUN_SPEED;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS){
		currentSpeed = RUN_SPEED;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS){
		currentTurnSpeed = -TURN_SPEED;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS){
		currentTurnSpeed = TURN_SPEED;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		jump();
	}

	// key released
	if (key == GLFW_KEY_W && action == GLFW_RELEASE){
		currentSpeed = 0;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE){
		currentSpeed = 0;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE){
		currentTurnSpeed = 0;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE){
		currentTurnSpeed = 0;
	}
}

void Player::move(){
	increaseRotation(0, currentTurnSpeed * Display::getFrameTimeSeconds(), 0);
	float distance = currentSpeed * Display::getFrameTimeSeconds();
	float dx = distance * sin(rotY);
	float dz = distance * cos(rotY);
	upwardsSpeed += GRAVITY * Display::getFrameTimeSeconds();
	increasePosition(dx, upwardsSpeed * Display::getFrameTimeSeconds(), dz);
	if (position.y < TERRAIN_HEIGHT){
		upwardsSpeed = 0;
		position.y = 0;
		isInAir = false;
	}
}

void Player::jump(){
	if(!isInAir){
		upwardsSpeed = JUMP_POWER;
		isInAir = true;
	}
}
