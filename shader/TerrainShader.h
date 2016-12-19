/*
 * TerrainShader.h
 *
 *  Created on: 07.11.2016
 *      Author: Philipp
 */

#ifndef TERRAINSHADER_H_
#define TERRAINSHADER_H_

#include "ShaderProgram.h"
#include "../toolbox/Maths.h"
#include "../entities/Light.h"

class TerrainShader : public ShaderProgram {
private:

	const char* VERTEX_FILE = "shaderfiles/TerrainVertexShader.txt";
	const char* FRAGMENT_FILE = "shaderfiles/TerrainFragmentShader.txt";

	GLint location_transformationMatrix;
	GLint location_projectionMatrix;
	GLint location_viewMatrix;
	GLint location_lightPosition;
	GLint location_lightColor;
	GLint location_shineDamper;
	GLint location_reflectivity;
	GLint location_skyColor;
	GLint location_backgroundTexture;
	GLint location_rTexture;
	GLint location_gTexture;
	GLint location_bTexture;
	GLint location_blendMap;


	void bindAttributes() override;
	void getAllUniformLocations() override;

public:

	TerrainShader();
	void loadTransformationMatrix(const glm::mat4& matrix);
	void loadProjectionMatrix(const glm::mat4& matrix);
	void loadViewMatrix(const Camera& camera);
	void loadLight(const Light& light);
	void loadShineVariables(float damper, float reflect);
	void loadSkyColor(float r, float b, float g);
	void connectTextureUnits();
};


#endif /* TERRAINSHADER_H_ */
