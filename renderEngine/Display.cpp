/*
 * DisplayManager.cpp
 *
 *  Created on: 04.11.2016
 *      Author: Philipp
 */

#include "Display.h"

#include <iostream>

float Display::delta = 0;

Display::Display() {
	if (!glfwInit()){
		std::cerr << "Error: GLFW initialization failed." << std::endl;
	}else{
		std::cout << "Initialized GLFW3 version " << glfwGetVersionString() << std::endl;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); //
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_REFRESH_RATE, FPS_CAP);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Game Window", NULL, NULL);
	if (!window){
		glfwTerminate();
		std::cerr << "Error creating Game Window." << std::endl;
		return;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Error: GLEW initialization failed." << std::endl;
    }else{
    	std::cout << "Initialized GLEW version " << glewGetString(GLEW_VERSION) << std::endl;
    }
	std::cout << std::endl;

	// key callbacks
	glfwSetKeyCallback(window, CallbackBase::keyCallback_dispatcher);
	glfwSetMouseButtonCallback(window, CallbackBase::mouseCallback_dispatcher);
	glfwSetScrollCallback(window, CallbackBase::scrollCallback_dispatcher);
	glfwSetCursorPosCallback(window, CallbackBase::cursorCallback_dispatcher);

	// timer
	lastFrameTime = getCurrentTime();
}

void Display::update(){
	glfwSwapBuffers(window);
	glfwPollEvents();
	long currentFrameTime = getCurrentTime();
	delta = (float) (currentFrameTime - lastFrameTime) / 1000;
	lastFrameTime = currentFrameTime;
}

void Display::close(){
	glfwDestroyWindow(window);
	glfwTerminate();
}

long Display::getCurrentTime(){
	auto now = std::chrono::high_resolution_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto epoch = now_ms.time_since_epoch();
	auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
	long time = value.count();
	return time;
}



