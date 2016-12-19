/*
 * StaticShader.cpp
 *
 *  Created on: 05.11.2016
 *      Author: Philipp
 */

#include "StaticShader.h"

StaticShader::StaticShader(){
	programID = loadShaders(VERTEX_FILE, FRAGMENT_FILE);
	getAllUniformLocations();
}

void StaticShader::bindAttributes(){
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
}

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

void StaticShader::loadTransformationMatrix(const glm::mat4& matrix){
	loadMatrix4f(location_transformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(const glm::mat4& matrix){
	loadMatrix4f(location_projectionMatrix, matrix);
}

void StaticShader::loadViewMatrix(const Camera& camera){
	loadMatrix4f(location_viewMatrix, Maths::createViewMatrix(camera));
}

void StaticShader::loadLight(const Light& light){
	loadVector3f(location_lightPosition, light.getPosition());
	loadVector3f(location_lightColor, light.getColor());
}

void StaticShader::loadShineVariables(float damper, float reflect){
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflect);
}

void StaticShader::loadFakeLightingVariable(bool useFake){
	loadBoolean(location_useFakeLighting, useFake);
}

void StaticShader::loadSkyColor(float r, float g, float b){
	loadVector3f(location_skyColor, glm::vec3(r,g,b));
}

