/*
 * Player.h
 *
 *  Created on: 15.12.2016
 *      Author: Philipp Gerber
 *
 *  The player class is a special type of entity that can be controlled by the user. it implements key callback methods
 *  for this purpose.
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <glm/glm.hpp>
#include <cmath>
#include <iostream>

#include "Entity.h"
#include "../models/TexturedModel.h"
#include "../toolbox/CallbackBase.h"
#include "../renderEngine/Display.h"
#include "../toolbox/Maths.h"

class Player: public Entity, public CallbackBase {
private:

	// physical constants
	const float RUN_SPEED = 20;
	const float TURN_SPEED = 2;
	const float GRAVITY = -50;
	const float JUMP_POWER = 30;

	// dummy terrain collision
	const float TERRAIN_HEIGHT = 0;

	// state variables
	float currentSpeed;
	float currentTurnSpeed;
	float upwardsSpeed;

	bool isInAir;


public:

	Player(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;

	void move();
	void jump();
};

#endif /* PLAYER_H_ */
