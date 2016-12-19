/*
 * TexturedModel.cpp
 *
 *  Created on: 05.11.2016
 *      Author: Philipp
 */

#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel m, ModelTexture t) : model{m}, texture{t} {
	ID = model.getVaoID();
}

RawModel TexturedModel::getRawModel(){
	return model;
}

ModelTexture TexturedModel::getModelTexture(){
	return texture;
}

bool operator<(const TexturedModel& lhs, const TexturedModel& rhs){
	return lhs.getID() < rhs.getID();
}
