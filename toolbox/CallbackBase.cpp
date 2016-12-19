/*
 * CallbackBase.cpp
 *
 *  Created on: 06.11.2016
 *      Author: Philipp
 */

#include "CallbackBase.h"
#include <iostream>

CallbackBase::~CallbackBase(){}

double CallbackBase::xpos_old = Display::WIDTH/2;
double CallbackBase::ypos_old = Display::HEIGHT/2;

std::list<CallbackBase*> CallbackBase::keyHandlingInstances;
std::list<CallbackBase*> CallbackBase::mouseHandlingInstances;
std::list<CallbackBase*> CallbackBase::scrollHandlingInstances;
std::list<CallbackBase*> CallbackBase::cursorHandlingInstances;


CallbackBase* CallbackBase::keyHandlingInstance;
CallbackBase* CallbackBase::mouseHandlingInstance;
CallbackBase* CallbackBase::scrollHandlingInstance;
CallbackBase* CallbackBase::cursorHandlingInstance;


void CallbackBase::setKeyHandling(){
	keyHandlingInstances.push_back(this);
}

void CallbackBase::setMouseHandling(){
	mouseHandlingInstances.push_back(this);
}

void CallbackBase::setScrollHandling(){
	scrollHandlingInstances.push_back(this);
}

void CallbackBase::setCursorHandling(){
	cursorHandlingInstances.push_back(this);
}


void CallbackBase::keyCallback_dispatcher(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(!keyHandlingInstances.empty()){
		for (auto i : keyHandlingInstances){
			i -> keyCallback(window, key, scancode, action, mods);
		}
	}
}

void CallbackBase::mouseCallback_dispatcher(GLFWwindow* window, int button, int action, int mods){
	if(!mouseHandlingInstances.empty()){
		for (auto i : mouseHandlingInstances){
			i -> mouseCallback(window, button, action, mods);
		}
	}
}

void CallbackBase::scrollCallback_dispatcher(GLFWwindow* window, double xoffset, double yoffset){
	if(!scrollHandlingInstances.empty()){
		for (auto i : scrollHandlingInstances){
			i -> scrollCallback(window, xoffset, yoffset);
		}
	}
}

void CallbackBase::cursorCallback_dispatcher(GLFWwindow* window, double xpos, double ypos){
	if(!cursorHandlingInstances.empty()){
		for (auto i : cursorHandlingInstances){
			i -> cursorCallback(window, xpos, ypos);
		}
	}
}


void CallbackBase::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){}

void CallbackBase::mouseCallback(GLFWwindow* window, int button, int action, int mods) {}

void CallbackBase::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {}

void CallbackBase::cursorCallback(GLFWwindow* window, double xpos, double ypos) {}


