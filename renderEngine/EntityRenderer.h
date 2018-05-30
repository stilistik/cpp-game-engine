/*
 * Renderer.h
 *
 *  Created on: 05.11.2016
 *      Author: Philipp Gerber
 *
 *  This is the renderer class for entities (game objects).
 */

#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_


#include <GL/glew.h>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <memory>
#include "../entities/Entity.h"
#include "../shader/StaticShader.h"
#include "../renderEngine/MasterRenderer.h"

class EntityRenderer {
private:

	// pointer to the corresponding shader instance
	StaticShader* shader;

public:

	EntityRenderer(StaticShader* s, glm::mat4& projectionMatrix);
	void render(std::map<TexturedModel, std::vector<Entity>> entities);
	void prepareTexturedModel(TexturedModel& model);
	void prepareInstance(Entity& entity);
	void unbindTexturedModel();
};

#endif /* ENTITYRENDERER_H_ */
