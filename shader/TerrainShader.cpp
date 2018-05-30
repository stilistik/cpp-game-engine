/*
 * TerrainShader.cpp
 *
 *  Created on: 07.11.2016
 *      Author: Philipp Gerber
 */

#include "TerrainShader.h"

/*
 * ctor: load and compile/link the shader, get all the locations of the uniform variables
 */
TerrainShader::TerrainShader(){
	programID = loadShaders(VERTEX_FILE, FRAGMENT_FILE);
	getAllUniformLocations();
}

/*
 * Bind the main VAO attributes to the corresponding locations in the shader
 */
void TerrainShader::bindAttributes(){
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}

/*
 * Get all locations of the uniform variables and store them as class members
 */
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

/*
 * Load up a transformation matrix to the shader
 */
void TerrainShader::loadTransformationMatrix(const glm::mat4& matrix){
	loadMatrix4f(location_transformationMatrix, matrix);
}

/*
 * Load up a projection matrix to the shader
 */
void TerrainShader::loadProjectionMatrix(const glm::mat4& matrix){
	loadMatrix4f(location_projectionMatrix, matrix);
}

/*
 * Load up a view matrix to the shader
 */
void TerrainShader::loadViewMatrix(const Camera& camera){
	loadMatrix4f(location_viewMatrix, Maths::createViewMatrix(camera));
}

/*
 * Load up a light source to the shader
 */
void TerrainShader::loadLight(const Light& light){
	loadVector3f(location_lightPosition, light.getPosition());
	loadVector3f(location_lightColor, light.getColor());
}

/*
 * Load up shine variables to the shader
 */
void TerrainShader::loadShineVariables(float damper, float reflect){
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflect);
}

/*
 * Load up the sky color to the shader
 */
void TerrainShader::loadSkyColor(float r, float g, float b){
	loadVector3f(location_skyColor, glm::vec3(r,g,b));
}

/*
 * Connect the textures of a TerrainTexturePack to the texture units in the shader
 */
void TerrainShader::connectTextureUnits(){
	loadInt(location_backgroundTexture, 0);
	loadInt(location_rTexture, 1);
	loadInt(location_gTexture, 2);
	loadInt(location_bTexture, 3);
	loadInt(location_blendMap, 4);
}

