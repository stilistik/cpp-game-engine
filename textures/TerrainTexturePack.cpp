/*
 * TerrainTexturePack.cpp
 *
 *  Created on: 09.11.2016
 *      Author: Philipp Gerber
 */

#include "TerrainTexturePack.h"

/*
 * ctor
 */
TerrainTexturePack::TerrainTexturePack(const TerrainTexture& bg, const TerrainTexture& r, const TerrainTexture& g, const TerrainTexture& b)
	: backgroundTexture{bg}, rTexture{r}, gTexture{g}, bTexture{b} {}
