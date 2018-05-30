/*
 * MasterRenderer.cpp
 *
 *  Created on: 07.11.2016
 *      Author: Philipp Gerber
 */

#include "MasterRenderer.h"

/*
 * ctor: Create the projection matrix (this is constant at runtime) and load it up to the different shader instances.
 */
MasterRenderer::MasterRenderer(){
	enableCulling(); // only front facing triangles are rendered
	createProjectionMatrix();
	staticShader = std::unique_ptr<StaticShader>(new StaticShader());
	entityRenderer = std::unique_ptr<EntityRenderer>( new EntityRenderer(staticShader.get(), projectionMatrix));
	terrainShader = std::unique_ptr<TerrainShader>(new TerrainShader());
	terrainRenderer = std::unique_ptr<TerrainRenderer>(new TerrainRenderer(terrainShader.get(), projectionMatrix));
}

/*
 * This prepares the renderer for the next frame.
 */
void MasterRenderer::prepare(){
	glEnable(GL_DEPTH_TEST); // perform the depth test so occluded triangles are not rendered
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(RED,GREEN,BLUE,1); // clear the color buffer
}

/*
 * Main render method
 */
void MasterRenderer::render(Light& sun, Camera& camera){
	prepare();

	// render entities
	staticShader->start();
	staticShader->loadSkyColor(RED, GREEN, BLUE);
	staticShader->loadLight(sun);
	staticShader->loadViewMatrix(camera);
	entityRenderer->render(entities);
	staticShader->stop();

	// render terrains
	terrainShader->start();
	terrainShader->loadSkyColor(RED, GREEN, BLUE);
	terrainShader->loadLight(sun);
	terrainShader->loadViewMatrix(camera);
	terrainRenderer->render(terrains);
	terrainShader->stop();

	// clear the list of terrains and entities, since they can change at runtime
	terrains.clear();
	entities.clear();
}

/*
 * This creates batches of entities that use the same textured model. This allows for batch rendering, where the model
 * is only loaded up once to the shaders and then rendered at different positions and orientations defined by the entity instances.
 */
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

/*
 * Static method to enableCulling after a transparent object was rendered
 */
void MasterRenderer::enableCulling(){
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

/*
 * Static method to disableCulling when rendering a transparent object
 */
void MasterRenderer::disableCulling(){
	glDisable(GL_CULL_FACE);
}

/*
 * This has to be called on program exit in order to delete the shader programs on the graphics unit
 */
void MasterRenderer::cleanUp(){
	staticShader->cleanUp();
	terrainShader->cleanUp();
}

/*
 * Helper method to create a projection matrix from frustum parameters
 */
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
