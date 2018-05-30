/*
 * TerrainRenderer.cpp
 *
 *  Created on: 07.11.2016
 *      Author: Philipp Gerber
 */

#include "TerrainRenderer.h"

/*
 * ctor: upload projection matrix to shader
 */
TerrainRenderer::TerrainRenderer(TerrainShader* s, glm::mat4& projectionMatrix) {
	shader = s;
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->connectTextureUnits();
	shader->stop();
}

/*
 * Main render method
 */
void TerrainRenderer::render(std::vector<Terrain>& terrains){
	for(Terrain terrain : terrains){
		prepareTerrain(terrain);
		loadModelMatrix(terrain);
		RawModel model = terrain.getModel();
		glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindTerrain();
	}
}

/*
 * Prepare a terrain for rendering. Get RawModel, bind VAO, enable attribute arrays, bind textures
 */
void TerrainRenderer::prepareTerrain(Terrain& terrain){
	RawModel rawModel = terrain.getModel();
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	bindTextures(terrain);
	shader->loadShineVariables(1,0);
}

/*
 * Bind the textures of a terrain. Terrains have texture packs consisting of a RGB blend map and corresponding textures for the RGB channels.
 * The BlendMap defines which texture gets rendered where on the terrain.
 */
void TerrainRenderer::bindTextures(Terrain& terrain){
	TerrainTexturePack texturePack = terrain.getTexturePack();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePack.getBackgroundTexture().getTextureID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturePack.getRTexture().getTextureID());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texturePack.getGTexture().getTextureID());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texturePack.getBTexture().getTextureID());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, terrain.getBlendMap().getTextureID());
}

/*
 * Unbind the terrain after it was rendered
 */
void TerrainRenderer::unbindTerrain(){
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

/*
 * Create a transformation matrix for the terrain and load it up to the shader
 */
void TerrainRenderer::loadModelMatrix(Terrain& terrain){
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(glm::vec3(terrain.getX(), 0, terrain.getZ()), 0, 0, 0, 1);
	shader->loadTransformationMatrix(transformationMatrix);
}
