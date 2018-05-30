/*
 * DisplayManager.h
 *
 *  Created on: 04.11.2016
 *
 *      Author: Philipp Gerber
 *
 *  This class represents an OpenGL render context. It also provides the functionality to compute the time
 *  elapsed since the last frame was rendered. This allows to make physical computations based on elapsed time.
 *
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>

#include "../toolbox/CallbackBase.h"

class Display {
private:

	long lastFrameTime;
	static float delta;

	long getCurrentTime();


public:

	static const int WIDTH = 1280;
	static const int HEIGHT = 720;
	static const int FPS_CAP = 120;

	GLFWwindow* window;

	Display();

	void createDisplay();
	void update();
	void close();
	static float getFrameTimeSeconds() { return delta; }


};

#endif /* DISPLAY_H_ */
