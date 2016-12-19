/*
 * Vertex.h
 *
 *  Created on: 09.11.2016
 *      Author: Philipp
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

	glm::vec3 position;

	int index;
	int textureIndex;
	int normalIndex;
	float length;

	bool duplicateFlag;
	VertexPointer duplicateVertex;

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
