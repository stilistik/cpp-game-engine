/*
 * OBJLoader.h
 *
 *  Created on: 06.11.2016
 *      Author: Philipp
 */

#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include "../models/RawModel.h"
#include "../renderEngine/Loader.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <glm/glm.hpp>

class OBJLoader {
private:

	static void parseInt(std::vector<std::string>& vertexData, std::vector<int>& vData);
	static void processVertex(std::vector<int>& vertexData, std::vector<int>& indices, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals, std::vector<float>& textureArray, std::vector<float>& normalsArray);

public:

	static RawModel loadObjModel(const char* fileName, Loader& loader);

};

#endif /* OBJLOADER_H_ */
