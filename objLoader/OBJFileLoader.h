/*
 * OBJLoader.h
 *
 *  Created on: 06.11.2016
 *      Author: Philipp
 */

#ifndef OBJFILELOADER_H_
#define OBJFILELOADER_H_

#include "../models/RawModel.h"
#include "../renderEngine/Loader.h"

#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <memory>
#include <glm/glm.hpp>
#include "../objLoader/Vertex.h"
#include "../objLoader/ModelData.h"

#include "OBJFileLoader.h"

class OBJFileLoader {
private:

	static void parseInt(std::vector<std::string>& vertexData, std::vector<int>& vData);
	static void processVertex(std::vector<int>& vertexData, std::vector<VertexPointer>& vertices, std::vector<int>& indices);
	static void dealWithProcessedVertex(VertexPointer previousVertex, int n_texIndex, int n_norIndex, std::vector<int>& indices, std::vector<VertexPointer>& vertices);
	static void removeUnusedVertices(std::vector<VertexPointer>& vertices);
	static float convertData(std::vector<VertexPointer>& vertices, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals, std::vector<float>& verticesArray, std::vector<float>& texturesArray, std::vector<float>& normalsArray);

public:

	static ModelData loadObjModel(const char* fileName, Loader& loader);

};

#endif /* OBJFILELOADER_H_ */
