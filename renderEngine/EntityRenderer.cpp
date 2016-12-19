/*
 * Renderer.cpp
 *
 *  Created on: 05.11.2016
 *      Author: Philipp
 */

#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(){
	shader = NULL;
}

EntityRenderer::EntityRenderer(std::shared_ptr<StaticShader> s, glm::mat4& projectionMatrix) {
	shader = s;
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

void EntityRenderer::render(std::map<TexturedModel, std::vector<Entity>> entities){
	for (auto pair : entities){
		TexturedModel model = pair.first;
		prepareTexturedModel(model);
		std::vector<Entity> batch = entities[model];
		for(Entity entity : batch){
			prepareInstance(entity);
			glDrawElements(GL_TRIANGLES, model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		unbindTexturedModel();
	}
}

void EntityRenderer::prepareTexturedModel(TexturedModel& model){
	RawModel rawModel = model.getRawModel();
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	ModelTexture texture = model.getModelTexture();
	if (texture.hasTransparency()){
		MasterRenderer::disableCulling();
	}
	shader->loadFakeLightingVariable(texture.useFakeLight());
	shader->loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
}

void EntityRenderer::unbindTexturedModel(){
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
	MasterRenderer::enableCulling();
}

void EntityRenderer::prepareInstance(Entity& entity){
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotX(), entity.getRotY(), entity.getRotZ(), entity.getScale());
	shader->loadTransformationMatrix(transformationMatrix);
}
