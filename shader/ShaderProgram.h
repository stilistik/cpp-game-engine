/*
 * ShaderProgram.h
 *
 *  Created on: 05.11.2016
 *      Author: Philipp Gerber
 *
 *
 *  The Base class for shader programs. This implements shader source parsing, compiling and linking of shader programs, as well as
 *  uploading of the most general datatypes as uniform variables to the shader program.
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class ShaderProgram {
protected:

	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	GLuint loadShaders(const char* vert, const char* frag);

	virtual void bindAttributes() = 0;
	void bindAttribute(int attribute, std::string variableName);

	virtual void getAllUniformLocations() = 0;
	GLint getUniformLocation(const char* uniformName);

	void loadInt(const int location, const int value);
	void loadFloat(const int location, const float value);
	void loadVector3f(const int location, const glm::vec3& v);
	void loadBoolean(const int location, const bool value);
	void loadMatrix4f(const int location, const glm::mat4& m);

public:

	virtual ~ShaderProgram();
	void start();
	void stop();
	void cleanUp();


};

#endif /* SHADERPROGRAM_H_ */
