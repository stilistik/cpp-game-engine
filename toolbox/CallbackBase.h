/*
 * CallbackBase.h
 *
 *  Created on: 06.11.2016
 *      Author: Philipp Gerber
 *
 *  This class is a callback base for the GLFW user input callback functions. We cannot define C++ class member functions as
 *  callbacks for GLFW, since it only accepts C-style functions without the 'this' argument. Hence, CallbackBase provides static
 *  dispatcher functions to use as callbacks for GLFW and maintains a list of handling instances. These handling instances inherit
 *  callback methods from CallBackBase. If the user then presses a key, the GLFW callback will call the callback-dispatcher
 *  functions, which in turn will call the callback methods of the individual handling instances.
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

	// collections of handler instances that are notified by the dispatchers
	static std::list<CallbackBase*> keyHandlingInstances;
	static std::list<CallbackBase*> mouseHandlingInstances;
	static std::list<CallbackBase*> scrollHandlingInstances;
	static std::list<CallbackBase*> cursorHandlingInstances;

	// virtual methods that can be overridden by the derived classes
	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {};
	virtual void mouseCallback(GLFWwindow* window, int button, int action, int mods) {};
	virtual void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {};
	virtual void cursorCallback(GLFWwindow* window, double xpos, double ypos) {};

	// called by derived classes to set them as handlers
	virtual void setKeyHandling();
	virtual void setMouseHandling();
	virtual void setScrollHandling();
	virtual void setCursorHandling();

	// static functions to serve as GLFW callbacks (no 'this' argument in static functions)
	static void keyCallback_dispatcher(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallback_dispatcher(GLFWwindow* window, int button, int action, int mods);
	static void scrollCallback_dispatcher(GLFWwindow* window, double xoffset, double yofsset);
	static void cursorCallback_dispatcher(GLFWwindow* window, double xpos, double ypos);

};

#endif /* CALLBACKBASE_H_ */
