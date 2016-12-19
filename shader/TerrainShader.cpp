/*
 * TerrainShader.cpp
 *
 *  Created on: 07.11.2016
 *      Author: Philipp
 */

#include "TerrainShader.h"


TerrainShader::TerrainShader(){
	programID = loadShaders(VERTEX_FILE, FRAGMENT_FILE);
	getAllUniformLocations();
}

void TerrainShader::bindAttributes(){
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
}

void TerrainShader::getAllUniformLocations(){
	location_transformationMatrix = getUniformLocation("transformationMatrix");
	location_projectionMatrix = getUniformLocation("projectionMatrix");
	location_viewMatrix = getUniformLocation("viewMatrix");
	location_lightPosition = getUniformLocation("lightPosition");
	location_lightColor = getUniformLocation("lightColor");
	location_shineDamper = getUniformLocation("shineDamper");
	location_reflectivity = getUniformLocation("reflectivity");
	location_skyColor = getUniformLocation("skyColor");
	location_backgroundTexture = getUniformLocation("backgroundTexture");
	location_rTexture = getUniformLocation("rTexture");
	location_gTexture = getUniformLocation("gTexture");
	location_bTexture = getUniformLocation("bTexture");
	location_blendMap = getUniformLocation("blendMap");
}

void TerrainShader::loadTransformationMatrix(const glm::mat4& matrix){
	loadMatrix4f(location_transformationMatrix, matrix);
}

void TerrainShader::loadProjectionMatrix(const glm::mat4& matrix){
	loadMatrix4f(location_projectionMatrix, matrix);
}

void TerrainShader::loadViewMatrix(const Camera& camera){
	loadMatrix4f(location_viewMatrix, Maths::createViewMatrix(camera));
}

void TerrainShader::loadLight(const Light& light){
	loadVector3f(location_lightPosition, light.getPosition());
	loadVector3f(location_lightColor, light.getColor());
}

void TerrainShader::loadShineVariables(float damper, float reflect){
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflect);
}

void TerrainShader::loadSkyColor(float r, float g, float b){
	loadVector3f(location_skyColor, glm::vec3(r,g,b));
}

void TerrainShader::connectTextureUnits(){
	loadInt(location_backgroundTexture, 0);
	loadInt(location_rTexture, 1);
	loadInt(location_gTexture, 2);
	loadInt(location_bTexture, 3);
	loadInt(location_blendMap, 4);
}
