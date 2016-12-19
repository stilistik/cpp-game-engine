/*
 * ShaderProgram.cpp
 *
 *  Created on: 05.11.2016
 *      Author: Philipp
 */

#include "ShaderProgram.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>

ShaderProgram::~ShaderProgram(){}

void ShaderProgram::start(){
	glUseProgram(programID);
}

void ShaderProgram::stop(){
	glUseProgram(0);
}

GLuint ShaderProgram::loadShaders(const char* vert, const char* frag){

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// read vertex shader
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vert, std::ios::in);
	if(vertexShaderStream.is_open()){
		std::string line = "";
		while(getline(vertexShaderStream, line)){
			vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	}else{
		std::cerr << "Could not open vertex shader file." << std::endl;
		return 0;
	}

	// read fragment shader
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(frag, std::ios::in);
	if(fragmentShaderStream.is_open()){
		std::string line = "";
		while(getline(fragmentShaderStream, line)){
			fragmentShaderCode += "\n" + line;
		}
		fragmentShaderStream.close();
	}else{
		std::cerr << "Could not open fragment shader file." << std::endl;
		return 0;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// compile vertex shader
	printf("Compiling shader: %s", vert);
	const char* vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	// check vertex shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0){
		std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		std::cout << &vertexShaderErrorMessage[0] << std::endl;
	}

	// compile fragment shader
	printf("Compiling shader: %s", frag);
	const char* fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	// check fragment shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0){
		std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		std::cout << &fragmentShaderErrorMessage[0] << std::endl;
	}

	// link program
	std::cout << "Linking shader program..." << std::endl;
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	bindAttributes();
	glLinkProgram(programID);
	glValidateProgram(programID);

	// check program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0){
		std::vector<char> programErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		std::cout << &programErrorMessage[0] << std::endl;
	}

	return programID;
}

void ShaderProgram::bindAttribute(int attribute, std::string variableName){
	glBindAttribLocation(programID, attribute, variableName.c_str());
}

GLint ShaderProgram::getUniformLocation(const char* uniformName){
	return glGetUniformLocation(programID, uniformName);
}

void ShaderProgram::loadInt(const int location, const int value){
	glUniform1i(location, value);
}

void ShaderProgram::loadFloat(const int location, const float value){
	glUniform1f(location, value);
}

void ShaderProgram::loadVector3f(const int location, const glm::vec3& v){
	glUniform3f(location, v.x, v.y, v.z);
}

void ShaderProgram::loadBoolean(const int location, const bool value){
	float toLoad;
	if (value){
		toLoad = 1;
	}
	glUniform1f(location, toLoad);
}

void ShaderProgram::loadMatrix4f(const int location, const glm::mat4& m){
	glUniformMatrix4fv(location, 1, false, &m[0][0]);
}


void ShaderProgram::cleanUp(){
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}


