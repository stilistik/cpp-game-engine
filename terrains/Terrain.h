/*
 * Terrain.h
 *
 *  Created on: 07.11.2016
 *      Author: Philipp Gerber
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "../models/RawModel.h"
#include "../textures/TerrainTexturePack.h"
#include "../textures/TerrainTexture.h"
#include "../renderEngine/Loader.h"


class Terrain {
private:


	const static float SIZE; // the size of a terrain patch
	const static int VERTEX_COUNT; // the vertex count of a terrain patch

	float x; // x coordinate of this terrain patch
	float z; // z coordinate of this terrain patch

	// model and textures of this terrain patch
	RawModel model;
	TerrainTexturePack texturePack;
	TerrainTexture blendMap;

	RawModel generateTerrain(Loader& loader);

public:

	Terrain(int gridX, int gridZ, Loader& loader, TerrainTexturePack tp, TerrainTexture bm);

	float getX() const { return x; }
	float getZ() const { return z; }
	const RawModel& getModel() const { return model; }
	TerrainTexture getBlendMap() const { return blendMap; }
	const TerrainTexturePack& getTexturePack() const { return texturePack; }
};

#endif /* TERRAIN_H_ */
