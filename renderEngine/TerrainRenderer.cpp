/*
 * TerrainRenderer.cpp
 *
 *  Created on: 07.11.2016
 *      Author: Philipp
 */

#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(){
	shader = NULL;
}

TerrainRenderer::TerrainRenderer(std::shared_ptr<TerrainShader> s, glm::mat4& projectionMatrix) {
	shader = s;
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->connectTextureUnits();
	shader->stop();
}

void TerrainRenderer::render(std::vector<Terrain>& terrains){
	for(Terrain terrain : terrains){
		prepareTerrain(terrain);
		loadModelMatrix(terrain);
		RawModel model = terrain.getModel();
		glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindTerrain();
	}
}

void TerrainRenderer::prepareTerrain(Terrain& terrain){
	RawModel rawModel = terrain.getModel();
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	bindTextures(terrain);
	shader->loadShineVariables(1,0);
}

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

void TerrainRenderer::unbindTerrain(){
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain& terrain){
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(glm::vec3(terrain.getX(), 0, terrain.getZ()), 0, 0, 0, 1);
	shader->loadTransformationMatrix(transformationMatrix);
}
