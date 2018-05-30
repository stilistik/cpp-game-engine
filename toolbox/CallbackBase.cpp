/*
 * CallbackBase.cpp
 *
 *  Created on: 06.11.2016
 *      Author: Philipp Gerber
 */

#include "CallbackBase.h"
#include <iostream>

CallbackBase::~CallbackBase(){}

// initialize mouse pos variables with display center coordinates
double CallbackBase::xpos_old = Display::WIDTH/2;
double CallbackBase::ypos_old = Display::HEIGHT/2;

// lists of handler instances
std::list<CallbackBase*> CallbackBase::keyHandlingInstances;
std::list<CallbackBase*> CallbackBase::mouseHandlingInstances;
std::list<CallbackBase*> CallbackBase::scrollHandlingInstances;
std::list<CallbackBase*> CallbackBase::cursorHandlingInstances;

/*
 * This can be called by a derived class to make it a key handler instance.
 */
void CallbackBase::setKeyHandling(){
	keyHandlingInstances.push_back(this);
}

/*
 * This can be called by a derived class to make it a mouse handler instance.
 */
void CallbackBase::setMouseHandling(){
	mouseHandlingInstances.push_back(this);
}

/*
 * This can be called by a derived class to make it a scroll wheel handler instance.
 */
void CallbackBase::setScrollHandling(){
	scrollHandlingInstances.push_back(this);
}

/*
 * This can be called by a derived class to make it a cursor handler instance.
 */
void CallbackBase::setCursorHandling(){
	cursorHandlingInstances.push_back(this);
}

/*
 * Key Callback Dispatcher: This method serves as a callback for GLFW when a key is pressed. It then notifies all the
 * key handler instances about the event
 */
void CallbackBase::keyCallback_dispatcher(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(!keyHandlingInstances.empty()){
		for (auto i : keyHandlingInstances){
			i -> keyCallback(window, key, scancode, action, mods);
		}
	}
}

/*
 * Mouse Callback Dispatcher: This method serves as a callback for GLFW when a mouse button is pressed. It then notifies all the
 * mouse handler instances about the event.
 */
void CallbackBase::mouseCallback_dispatcher(GLFWwindow* window, int button, int action, int mods){
	if(!mouseHandlingInstances.empty()){
		for (auto i : mouseHandlingInstances){
			i -> mouseCallback(window, button, action, mods);
		}
	}
}

/*
 * Scroll Callback Dispatcher: This method serves as a callback for GLFW when the mouse wheel is moved. It then notifies all the
 * scoll handler instances about the event.
 */
void CallbackBase::scrollCallback_dispatcher(GLFWwindow* window, double xoffset, double yoffset){
	if(!scrollHandlingInstances.empty()){
		for (auto i : scrollHandlingInstances){
			i -> scrollCallback(window, xoffset, yoffset);
		}
	}
}

/*
 * Cursor Callback Dispatcher: This method serves as a callback for GLFW when the mouse is moved. It then notifies all the
 * cursor handler instances about the event.
 */
void CallbackBase::cursorCallback_dispatcher(GLFWwindow* window, double xpos, double ypos){
	if(!cursorHandlingInstances.empty()){
		for (auto i : cursorHandlingInstances){
			i -> cursorCallback(window, xpos, ypos);
		}
	}
}




