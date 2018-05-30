/*
 * Player.cpp
 *
 *  Created on: 15.12.2016
 *      Author: Philipp
 */

#include "Player.h"

/*
 * ctor
 */
Player::Player(TexturedModel m, glm::vec3 pos, float rX, float rY, float rZ, float s)
	: Entity(m, pos, rX, rY, rZ, s) , currentSpeed{0}, currentTurnSpeed{0}, upwardsSpeed{0}, isInAir{false} {
		setKeyHandling();
	}

/*
 * Main KeyCallback method. This is called by the dispatcher function of CallbackBase and it is used to set the state
 * variables of the Player.
 */
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

/*
 * Main update method of the player object. This is called during each iteration of the main render loop. Speed constants are
 * multiplied by the time that passed since the last frame to obtain distances or rotation angles. These are the added to the
 * current position or rotation using the methods inherited from Entity.
 */
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

/*
 * This method is called when the space bar is pressed by the user. UpwardsSpeed is set to the players jump power and then
 * reduced by the gravity constant during each call of the Player::move() method.
 */
void Player::jump(){
	if(!isInAir){
		upwardsSpeed = JUMP_POWER;
		isInAir = true;
	}
}
