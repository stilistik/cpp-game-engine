/*
 * TexturedModel.cpp
 *
 *  Created on: 05.11.2016
 *      Author: Philipp Gerber
 */

#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel m, ModelTexture t) : model{m}, texture{t} {
	ID = model.getVaoID();
}
/*
 * Get the raw model
 */
RawModel TexturedModel::getRawModel(){
	return model;
}

/*
 * Get the texture
 */
ModelTexture TexturedModel::getModelTexture(){
	return texture;
}

/*
 * Comparator for two TexturedModels, used for sorting
 */
bool operator<(const TexturedModel& lhs, const TexturedModel& rhs){
	return lhs.getID() < rhs.getID();
}
