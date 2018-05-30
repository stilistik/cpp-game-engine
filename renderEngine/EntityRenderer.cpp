/*
 * Renderer.cpp
 *
 *  Created on: 05.11.2016
 *      Author: Philipp Gerber
 */

#include "EntityRenderer.h"


/*
 * ctor
 */
EntityRenderer::EntityRenderer(StaticShader* s, glm::mat4& projectionMatrix) {
	shader = s;
	shader->start(); // we need to start the shader before we can upload a uniform variable
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

/*
 * Main render method of the EntityRenderer. This takes in a map of textured models and entities, so we can render the entities
 * in batches of instances that use the same textured model.
 */
void EntityRenderer::render(std::map<TexturedModel, std::vector<Entity>> entities){
	for (auto pair : entities){
		TexturedModel model = pair.first;

		// prepare OpenGL to render the model of the entity batch
		prepareTexturedModel(model);
		std::vector<Entity> batch = entities[model];

		for(Entity entity : batch){
			// compute transformation matrix for each entity and load it up to the shader
			// we render the same model for the entire batch, just with different transformation matrices
			prepareInstance(entity);

			// main OpenGL render method
			glDrawElements(GL_TRIANGLES, model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		unbindTexturedModel();
	}
}

/*
 * This gets the RawModel instance of a textured model, binds its VAO, enables its attribute arrays. Then it gets
 * the model texture and binds it.
 */
void EntityRenderer::prepareTexturedModel(TexturedModel& model){
	RawModel rawModel = model.getRawModel();
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0); // vertex positions
	glEnableVertexAttribArray(1); // normals
	glEnableVertexAttribArray(2); // texture coordinates
	ModelTexture texture = model.getModelTexture();

	// if the texture has transparency, we want to disable culling.
	if (texture.hasTransparency()){
		MasterRenderer::disableCulling();
	}

	// fake lighting applies to flat models like grass. we want it to be illuminated at all times.
	shader->loadFakeLightingVariable(texture.useFakeLight());

	// shine variables for the blinn shader model
	shader->loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
}

/*
 * After the model has been rendered, we unbind the data from OpenGL
 */
void EntityRenderer::unbindTexturedModel(){
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
	MasterRenderer::enableCulling();
}

/*
 * This computes a transformation matrix from an Entity's position and orientation, then loads it up to the shader.
 */
void EntityRenderer::prepareInstance(Entity& entity){
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotX(), entity.getRotY(), entity.getRotZ(), entity.getScale());
	shader->loadTransformationMatrix(transformationMatrix);
}
