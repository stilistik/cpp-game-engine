/*
 * DisplayManager.cpp
 *
 *  Created on: 04.11.2016
 *      Author: Philipp Gerber
 */

#include "Display.h"

#include <iostream>
#include <chrono>


float Display::delta = 0;

/*
 * ctor
 */
Display::Display() {
	if (!glfwInit()){
		std::cerr << "Error: GLFW initialization failed." << std::endl;
	}else{
		std::cout << "Initialized GLFW3 version " << glfwGetVersionString() << std::endl;
	}

	// setup the OpenGL context
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL version
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_REFRESH_RATE, FPS_CAP); // set max FPS
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// create the window
	window = glfwCreateWindow(WIDTH, HEIGHT, "Game Window", NULL, NULL);
	if (!window){
		glfwTerminate();
		std::cerr << "Error creating Game Window." << std::endl;
		return;
	}
	glfwMakeContextCurrent(window); // make window the currently active render context

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Error: GLEW initialization failed." << std::endl;
    }else{
    	std::cout << "Initialized GLEW version " << glewGetString(GLEW_VERSION) << std::endl;
    }
	std::cout << std::endl;

	// set the key callbacks - these have to be C-style functions, so we use a CallbackBase class with static dispatcher methods
	glfwSetKeyCallback(window, CallbackBase::keyCallback_dispatcher);
	glfwSetMouseButtonCallback(window, CallbackBase::mouseCallback_dispatcher);
	glfwSetScrollCallback(window, CallbackBase::scrollCallback_dispatcher);
	glfwSetCursorPosCallback(window, CallbackBase::cursorCallback_dispatcher);

	// initialize timer
	lastFrameTime = getCurrentTime();
}

/*
 * The main display update method. This has to be called for each iteration of the main render loop
 */
void Display::update(){
	glfwSwapBuffers(window); // update the display buffers
	glfwPollEvents(); // process all events, this calls the callback functions set in the constructor

	// compute the elapsed time since the last frame
	long currentFrameTime = getCurrentTime();
	delta = (float) (currentFrameTime - lastFrameTime) / 1000;
	lastFrameTime = currentFrameTime;
}

/*
 * Close the display. Has to be called at the end of the program.
 */
void Display::close(){
	glfwDestroyWindow(window);
	glfwTerminate();
}

/*
 * Helper method to get the current time
 */
long Display::getCurrentTime(){
	auto now = std::chrono::high_resolution_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto epoch = now_ms.time_since_epoch();
	auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
	long time = value.count();
	return time;
}



