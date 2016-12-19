/*
 * ModelData.h
 *
 *  Created on: 09.11.2016
 *      Author: Philipp
 */

#ifndef MODELDATA_H_
#define MODELDATA_H_

#include <vector>

class ModelData {
private:

	std::vector<float> vertices;
	std::vector<float> texCoords;
	std::vector<float> normals;
	std::vector<int> indices;
	float furthestPoint;

public:

	ModelData(const std::vector<float>& v, const std::vector<float>& t, const std::vector<float> n, const std::vector<int> i, float fp);

	const std::vector<int>& getIndices() const { return indices; }
	const std::vector<float>& getNormals() const { return normals; }
	const std::vector<float>& getTexCoords() const { return texCoords; }
	const std::vector<float>& getVertices() const {	return vertices; }
	float getFurthestPoint() const { return furthestPoint; }

};

#endif /* MODELDATA_H_ */
