/*
 * StaticShader.h
 *
 *  Created on: 05.11.2016
 *      Author: Philipp
 */

#ifndef STATICSHADER_H_
#define STATICSHADER_H_

#include "ShaderProgram.h"
#include "../toolbox/Maths.h"
#include "../entities/Light.h"

class StaticShader : public ShaderProgram {
private:

	const char* VERTEX_FILE = "shaderfiles/VertexShader.txt";
	const char* FRAGMENT_FILE = "shaderfiles/FragmentShader.txt";

	GLint location_transformationMatrix;
	GLint location_projectionMatrix;
	GLint location_viewMatrix;
	GLint location_lightPosition;
	GLint location_lightColor;
	GLint location_shineDamper;
	GLint location_reflectivity;
	GLint location_useFakeLighting;
	GLint location_skyColor;

	void bindAttributes() override;
	void getAllUniformLocations() override;

public:

	StaticShader();
	void loadTransformationMatrix(const glm::mat4& matrix);
	void loadProjectionMatrix(const glm::mat4& matrix);
	void loadViewMatrix(const Camera& camera);
	void loadLight(const Light& light);
	void loadShineVariables(float damper, float reflect);
	void loadFakeLightingVariable(bool useFake);
	void loadSkyColor(float r, float g, float b);
};

#endif /* STATICSHADER_H_ */
