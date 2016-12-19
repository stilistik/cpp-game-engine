/*
 * CallbackBase.h
 *
 *  Created on: 06.11.2016
 *      Author: Philipp
 */

#ifndef CALLBACKBASE_H_
#define CALLBACKBASE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <list>

#include "../renderEngine/Display.h"

class CallbackBase {
protected:

	static double xpos_old;
	static double ypos_old;

public:

	virtual ~CallbackBase();

	static std::list<CallbackBase*> keyHandlingInstances;
	static std::list<CallbackBase*> mouseHandlingInstances;
	static std::list<CallbackBase*> scrollHandlingInstances;
	static std::list<CallbackBase*> cursorHandlingInstances;

	static CallbackBase* keyHandlingInstance;
	static CallbackBase* mouseHandlingInstance;
	static CallbackBase* scrollHandlingInstance;
	static CallbackBase* cursorHandlingInstance;

	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	virtual void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	virtual void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	virtual void cursorCallback(GLFWwindow* window, double xpos, double ypos);

	virtual void setKeyHandling();
	virtual void setMouseHandling();
	virtual void setScrollHandling();
	virtual void setCursorHandling();

	static void keyCallback_dispatcher(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallback_dispatcher(GLFWwindow* window, int button, int action, int mods);
	static void scrollCallback_dispatcher(GLFWwindow* window, double xoffset, double yofsset);
	static void cursorCallback_dispatcher(GLFWwindow* window, double xpos, double ypos);

};

#endif /* CALLBACKBASE_H_ */
