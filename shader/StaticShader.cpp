/*
 * StaticShader.cpp
 *
 *  Created on: 05.11.2016
 *      Author: Philipp Gerber
 */

#include "StaticShader.h"

/*
 * ctor: load and compile/link the shader, get all the locations of the uniform variables
 */
StaticShader::StaticShader(){
	programID = loadShaders(VERTEX_FILE, FRAGMENT_FILE);
	getAllUniformLocations();
}

/*
 * Bind the main VAO attributes to the corresponding locations in the shader
 */
void StaticShader::bindAttributes(){
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}

/*
 * Get all locations of the uniform variables and store them as class members
 */
void StaticShader::getAllUniformLocations(){
	location_transformationMatrix = getUniformLocation("transformationMatrix");
	location_projectionMatrix = getUniformLocation("projectionMatrix");
	location_viewMatrix = getUniformLocation("viewMatrix");
	location_lightPosition = getUniformLocation("lightPosition");
	location_lightColor = getUniformLocation("lightColor");
	location_shineDamper = getUniformLocation("shineDamper");
	location_reflectivity = getUniformLocation("reflectivity");
	location_useFakeLighting = getUniformLocation("useFakeLighting");
	location_skyColor = getUniformLocation("skyColor");
}

/*
 * Load up a transformation matrix to the shader
 */
void StaticShader::loadTransformationMatrix(const glm::mat4& matrix){
	loadMatrix4f(location_transformationMatrix, matrix);
}

/*
 * Load up a projection matrix to the shader
 */
void StaticShader::loadProjectionMatrix(const glm::mat4& matrix){
	loadMatrix4f(location_projectionMatrix, matrix);
}

/*
 * Load up a view matrix to the shader
 */
void StaticShader::loadViewMatrix(const Camera& camera){
	loadMatrix4f(location_viewMatrix, Maths::createViewMatrix(camera));
}

/*
 * Load up a light source to the shader
 */
void StaticShader::loadLight(const Light& light){
	loadVector3f(location_lightPosition, light.getPosition());
	loadVector3f(location_lightColor, light.getColor());
}

/*
 * Load up shine variables to the shader
 */
void StaticShader::loadShineVariables(float damper, float reflect){
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflect);
}

/*
 * Load up fake lighting boolean to the shader
 */
void StaticShader::loadFakeLightingVariable(bool useFake){
	loadBoolean(location_useFakeLighting, useFake);
}

/*
 * Load up the sky color to the shader
 */
void StaticShader::loadSkyColor(float r, float g, float b){
	loadVector3f(location_skyColor, glm::vec3(r,g,b));
}

