/*
 * TexturedModel.h
 *
 *  Created on: 05.11.2016
 *      Author: Philipp
 */

#ifndef TEXTUREDMODEL_H_
#define TEXTUREDMODEL_H_

#include "RawModel.h"
#include "../textures/ModelTexture.h"

class TexturedModel {
private:

	RawModel model;
	ModelTexture texture;
	int ID;

public:

	TexturedModel(RawModel mo, ModelTexture t);
	RawModel getRawModel();
	ModelTexture getModelTexture();
	int getID() const {	return ID; }
};

bool operator<(const TexturedModel& lhs, const TexturedModel& rhs);

#endif /* TEXTUREDMODEL_H_ */
