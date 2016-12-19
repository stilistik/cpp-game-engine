/*
 * TerrainTexturePack.cpp
 *
 *  Created on: 09.11.2016
 *      Author: Philipp
 */

#include "TerrainTexturePack.h"

TerrainTexturePack::TerrainTexturePack(const TerrainTexture& bg, const TerrainTexture& r, const TerrainTexture& g, const TerrainTexture& b)
	: backgroundTexture{bg}, rTexture{r}, gTexture{g}, bTexture{b} {}
