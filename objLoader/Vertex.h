/*
 * Vertex.h
 *
 *  Created on: 09.11.2016
 *      Author: Philipp Gerber
 *
 *  This class is a simple representation of a vertex. It serves as a container for sorting of vertex data
 *  in the OBJFileLoader.
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <glm/glm.hpp>
#include <memory>

class Vertex;
typedef std::shared_ptr<Vertex> VertexPointer;


class Vertex {
private:

	const static int NO_INDEX;

	// vertex coordinates
	glm::vec3 position;

	int index; // index buffer index
	int textureIndex; // index of corresponding texture coordinates
	int normalIndex; // index of corresponding normal vector
	float length; // length of the vertex computed from the origin

	bool duplicateFlag; // vertex with the same position already exists
	VertexPointer duplicateVertex; // pointer to vertex with same position

public:

	Vertex(const glm::vec3& p, int index);

	bool isSet();
	bool hasSameTexNor(int ti_other, int ni_other);

	// getter & setter
	int getIndex() const { return index; }
	float getLength() const { return length; }
	int getNormalIndex() const { return normalIndex; }
	void setNormalIndex(int ni) { normalIndex = ni; }
	const glm::vec3& getPosition() const { return position; }
	int getTextureIndex() const { return textureIndex; }
	void setTextureIndex(int ti) { textureIndex = ti; }
	VertexPointer getDuplicateVertex() const {	return duplicateVertex; }
	bool hasDuplicateVertex() { return duplicateFlag; }
	void setDuplicateVertex(VertexPointer dv) { duplicateVertex = dv; duplicateFlag = true; }

};

#endif /* VERTEX_H_ */
