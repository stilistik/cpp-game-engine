/*
 * ModelData.h
 *
 *  Created on: 09.11.2016
 *      Author: Philipp Gerber
 *
 *  A simple container data structure for geometric model data. Stores vertices, normals, texture coordinates and indices.
 */

#ifndef MODELDATA_H_
#define MODELDATA_H_

#include <vector>

class ModelData {
private:

	// data
	std::vector<float> vertices;
	std::vector<float> texCoords;
	std::vector<float> normals;
	std::vector<int> indices;
	float furthestPoint; // furthest point from the models

public:

	ModelData(const std::vector<float>& v, const std::vector<float>& t, const std::vector<float> n, const std::vector<int> i, float fp);

	const std::vector<int>& getIndices() const { return indices; }
	const std::vector<float>& getNormals() const { return normals; }
	const std::vector<float>& getTexCoords() const { return texCoords; }
	const std::vector<float>& getVertices() const {	return vertices; }
	float getFurthestPoint() const { return furthestPoint; }

};

#endif /* MODELDATA_H_ */
