/*
 * Camera.h
 *
 *  Created on: 06.11.2016
 *      Author: Philipp
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
#include <iostream>
#include <cmath>

#include "../toolbox/CallbackBase.h"
#include "../entities/Player.h"

class Player;

typedef std::shared_ptr<Player> PlayerPointer;

class Camera : public CallbackBase{
private:

	PlayerPointer player;

	const float maxCamVelocity = 100;
	const float resetSpeed = 1;

	float distanceFromPlayer = 50;
	float angleAroundPlayer = 0;

	glm::vec3 position;
	float pitch;
	float yaw;
	float roll;

	bool button1_pressed = false;
	bool button2_pressed = false;
	bool resetAngle = false;

public:

	Camera(PlayerPointer p);

	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	virtual void mouseCallback(GLFWwindow* window, int button, int action, int mods) override;
	virtual void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) override;
	virtual void cursorCallback(GLFWwindow* window, double xpos, double ypos) override;



	void move();
	float getPitch() const { return pitch; }
	const glm::vec3& getPosition() const { return position; }
	float getRoll() const { return roll; }
	float getYaw() const { return yaw; }
};

#endif /* CAMERA_H_ */
