/*
 * TerrainTexturePack.h
 *
 *  Created on: 09.11.2016
 *      Author: Philipp Gerber
 *
 *  This class represents a collection of 4 different terrain textures. These textures are then blended together in the shader
 *  using a blend map
 */

#ifndef TERRAINTEXTUREPACK_H_
#define TERRAINTEXTUREPACK_H_

#include "../textures/TerrainTexture.h"

class TerrainTexturePack {
private:

	TerrainTexture backgroundTexture;
	TerrainTexture rTexture;
	TerrainTexture gTexture;
	TerrainTexture bTexture;

public:

	TerrainTexturePack(const TerrainTexture& bg, const TerrainTexture& r, const TerrainTexture& g, const TerrainTexture& b);
	TerrainTexture getBackgroundTexture() const { return backgroundTexture; }
	TerrainTexture getRTexture() const { return bTexture; }
	TerrainTexture getGTexture() const { return gTexture; }
	TerrainTexture getBTexture() const { return rTexture; }
};

#endif /* TERRAINTEXTUREPACK_H_ */
