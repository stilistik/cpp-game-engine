/*
 * TerrainTexture.h
 *
 *  Created on: 09.11.2016
 *      Author: Philipp Gerber
 *
 *  This is a simple container class for a terrain texture
 */

#ifndef TERRAINTEXTURE_H_
#define TERRAINTEXTURE_H_

#include <GL/glew.h>

class TerrainTexture {
private:

	GLint textureID;

public:

	TerrainTexture(GLint id);
	GLint getTextureID() const { return textureID; }
};

#endif /* TERRAINTEXTURE_H_ */
