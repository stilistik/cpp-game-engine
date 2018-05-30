/*
 * MasterRenderer.h
 *
 *  Created on: 07.11.2016
 *      Author: Philipp Gerber
 *
 *
 *  This is the main renderer class of this application. It coordinates rendering of different structures. At the moment
 *  we have an EntityRenderer and a TerrainRenderer. There will also be specialized renderers for Skyboxes, Water, animated Entities etc.
 */

#ifndef MASTERRENDERER_H_
#define MASTERRENDERER_H_

#include <vector>
#include <map>
#include <memory>

#include "../renderEngine/EntityRenderer.h"
#include "../shader/StaticShader.h"
#include "../renderEngine/TerrainRenderer.h"
#include "../shader/TerrainShader.h"

#include "../models/TexturedModel.h"
#include "../entities/Entity.h"
#include "../entities/Camera.h"
#include "../entities/Light.h"
#include "../renderEngine/Display.h"
#include "../toolbox/Maths.h"

// forward declarations
class EntityRenderer;
class TerrainRenderer;


class MasterRenderer {
private:

	// frustum parameters
	const float FOV = 70;
	const float NEAR_PLANE = 0.1;
	const float FAR_PLANE = 1000;
	glm::mat4 projectionMatrix;
	void createProjectionMatrix();

	// background clear color
	const float RED = 0.4;
	const float GREEN = 0.6;
	const float BLUE = 0.7;

	// pointers to the different shader and renderer instances
	std::unique_ptr<StaticShader> staticShader;
	std::unique_ptr<EntityRenderer> entityRenderer;
	std::unique_ptr<TerrainShader> terrainShader;
	std::unique_ptr<TerrainRenderer> terrainRenderer;

	// map of entities and list of terrains
	std::map<TexturedModel, std::vector<Entity>> entities;
	std::vector<Terrain> terrains;


public:

	// ctor & dtor
	MasterRenderer();
	MasterRenderer(const MasterRenderer&) = delete;

	// member functions
	void prepare();
	void processEntity(Entity& entity);
	void processTerrain(Terrain& terrain);
	void static enableCulling();
	void static disableCulling();
	void render(Light& sun, Camera& camera);
	void cleanUp();
};

#endif /* MASTERRENDERER_H_ */
