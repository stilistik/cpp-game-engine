/*
 * ModelData.cpp
 *
 *  Created on: 09.11.2016
 *      Author: Philipp Gerber
 */

#include "ModelData.h"

// ctor
ModelData::ModelData(const std::vector<float>& v, const std::vector<float>& t, const std::vector<float> n, const std::vector<int> i, float fp)
	: vertices{v}, texCoords{t}, normals{n}, indices{i}, furthestPoint{fp} {}


