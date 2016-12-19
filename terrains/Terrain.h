/*
 * Terrain.h
 *
 *  Created on: 07.11.2016
 *      Author: Philipp
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "../models/RawModel.h"
#include "../textures/TerrainTexturePack.h"
#include "../textures/TerrainTexture.h"
#include "../renderEngine/Loader.h"


class Terrain {
private:

	const static float SIZE;;
	const static int VERTEX_COUNT;;

	float x;
	float z;
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
