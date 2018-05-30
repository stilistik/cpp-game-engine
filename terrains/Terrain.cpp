/*
 * Terrain.cpp
 *
 *  Created on: 07.11.2016
 *      Author: Philipp Gerber
 */

#include "Terrain.h"

#include <iostream>

// constant definitions
const float Terrain::SIZE = 800;
const int Terrain::VERTEX_COUNT = 128;

/*
 * ctor: gridX and gridY specify the coordinates of this terrain patch in a grid of terrain patches.
 */
Terrain::Terrain(int gridX, int gridZ, Loader& loader, TerrainTexturePack tp, TerrainTexture bm)
	: texturePack{tp}, blendMap{bm} {
	x = gridX * SIZE; // multiply grid coordinates by patch size to get absolute coordinate
	z = gridZ * SIZE;
	model = generateTerrain(loader);
}

/*
 * This method creates a raw model for terrains. The model for a terrain is a flat grid of vertices connected to triangles.
 */
RawModel Terrain::generateTerrain(Loader& loader){
	int count = VERTEX_COUNT * VERTEX_COUNT; // total vertex count

	// create empty containers for vertices, normals, texture coordinates and indices
	std::vector<float> vertices(count * 3);
	std::vector<float> normals(count * 3);
	std::vector<float> textureCoords(count * 2);
	std::vector<int> indices(6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1));

	// procedural generation of the terrain grid
	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++){
		for (int j = 0; j < VERTEX_COUNT; j++){
			// create vertex positions
			vertices[vertexPointer*3] = (float)j/((float)VERTEX_COUNT - 1) * SIZE;
			vertices[vertexPointer*3+1] = 0; // y coordinate is zero for all vertices, since the terrain is flat
			vertices[vertexPointer*3+2] = (float)i/((float)VERTEX_COUNT - 1) * SIZE;

			// create normals that are pointing upwards for the flat terrain
			normals[vertexPointer*3] = 0;
			normals[vertexPointer*3+1] = 1;
			normals[vertexPointer*3+2] = 0;

			// create texture coordinates
			textureCoords[vertexPointer*2] = (float)j/((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer*2+1] = (float)i/((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}

	// create the index buffer so that the vertices are connected to triangles
	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++){
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++){
			// compute the vertex indices of the grid cells, starting with the top left grid cell
			int topLeft = (gz * VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;

			// one grid cell consists of two triangles, set index buffer accordingly
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	// return the raw model
	return loader.loadToVAO(vertices, textureCoords, normals, indices);
}
