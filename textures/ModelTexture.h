/*
 * ModelTexture.h
 *
 *  Created on: 05.11.2016
 *      Author: Philipp Gerber
 *
 *  This class represents a texture for a textured model
 */

#ifndef MODELTEXTURE_H_
#define MODELTEXTURE_H_

#include <GL/glew.h>

class ModelTexture {
private:

	GLuint textureID;
	float shineDamper;
	float reflectivity;
	bool transparency;
	bool fakeLight;

public:

	ModelTexture(GLuint id);

	// getter & setter
	GLuint getTextureID() const { return textureID; }
	float getReflectivity() const {	return reflectivity; }
	void setReflectivity(float r) { reflectivity = r; }
	float getShineDamper() const { return shineDamper; }
	void setShineDamper(float sD) { shineDamper = sD; }
	bool hasTransparency() const { return transparency; }
	void setHasTransparency(bool t) { transparency = t;	}
	bool useFakeLight() const { return fakeLight; }
	void setFakeLight(bool fL) {fakeLight = fL; }


};

#endif /* MODELTEXTURE_H_ */
