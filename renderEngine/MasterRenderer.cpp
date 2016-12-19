/*
 * MasterRenderer.cpp
 *
 *  Created on: 07.11.2016
 *      Author: Philipp
 */

#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(){
	enableCulling();
	createProjectionMatrix();
	staticShader = std::shared_ptr<StaticShader>(new StaticShader());
	entityRenderer = std::shared_ptr<EntityRenderer>( new EntityRenderer(staticShader, projectionMatrix));
	terrainShader = std::shared_ptr<TerrainShader>(new TerrainShader());
	terrainRenderer = std::shared_ptr<TerrainRenderer>(new TerrainRenderer(terrainShader, projectionMatrix));
}

MasterRenderer::~MasterRenderer(){}

void MasterRenderer::prepare(){
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(RED,GREEN,BLUE,1);
}

void MasterRenderer::render(Light& sun, Camera& camera){
	prepare();
	staticShader->start();
	staticShader->loadSkyColor(RED, GREEN, BLUE);
	staticShader->loadLight(sun);
	staticShader->loadViewMatrix(camera);
	entityRenderer->render(entities);
	staticShader->stop();

	terrainShader->start();
	terrainShader->loadSkyColor(RED, GREEN, BLUE);
	terrainShader->loadLight(sun);
	terrainShader->loadViewMatrix(camera);
	terrainRenderer->render(terrains);
	terrainShader->stop();

	terrains.clear();
	entities.clear();
}

void MasterRenderer::processEntity(Entity& entity){
	TexturedModel model = entity.getModel();
	std::vector<Entity> batch = entities[model];
	if(batch.empty()){
		std::vector<Entity> newBatch;
		newBatch.push_back(entity);
		entities[model] = newBatch;
	}else{
		batch.push_back(entity);
		entities[model] = batch;
	}
}

void MasterRenderer::processTerrain(Terrain& terrain){
	terrains.push_back(terrain);
}

void MasterRenderer::enableCulling(){
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MasterRenderer::disableCulling(){
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::cleanUp(){
	staticShader->cleanUp();
	terrainShader->cleanUp();
}

void MasterRenderer::createProjectionMatrix(){
	float aspectRatio = (float) Display::WIDTH / (float) Display::HEIGHT;
	float y_scale = (float) ((1 / tan(Maths::toRadians(FOV/2))) * aspectRatio);
	float x_scale = y_scale / aspectRatio;
	float frustum_length = FAR_PLANE - NEAR_PLANE;
	projectionMatrix = glm::mat4(0.0);
	projectionMatrix[0][0] = x_scale;
	projectionMatrix[1][1] = y_scale;
	projectionMatrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
	projectionMatrix[2][3] = -1;
	projectionMatrix[3][2] = -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length);
	projectionMatrix[3][3] = 0;
}
