/*
 * ModelTexture.cpp
 *
 *  Created on: 05.11.2016
 *      Author: Philipp Gerber
 */

#include "ModelTexture.h"

/*
 * ctor
 */
ModelTexture::ModelTexture(GLuint id)
	: textureID{id} , shineDamper{1}, reflectivity{0} , transparency{false}, fakeLight{false} {}
