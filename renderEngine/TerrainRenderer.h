/*
 * TerrainRenderer.h
 *
 *  Created on: 07.11.2016
 *      Author: Philipp
 */

#ifndef TERRAINRENDERER_H_
#define TERRAINRENDERER_H_


#include <GL/glew.h>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <memory>
#include "../renderEngine/Display.h"
#include "../shader/TerrainShader.h"
#include "../terrains/Terrain.h"
#include "../models/TexturedModel.h"

class TerrainRenderer {
private:

	std::shared_ptr<TerrainShader> shader;

public:

	TerrainRenderer();
	TerrainRenderer(std::shared_ptr<TerrainShader> s, glm::mat4& projectionMatrix);
	void render(std::vector<Terrain>& terrains);
	void prepareTerrain(Terrain& terrain);
	void bindTextures(Terrain& terrain);
	void loadModelMatrix(Terrain& terrain);
	void unbindTerrain();
};

#endif /* TERRAINRENDERER_H_ */
