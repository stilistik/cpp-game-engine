
#include <vector>
#include <fstream>
#include <iostream>
#include <ios>
#include <cstdlib>
#include <glm/glm.hpp>

#include "../renderEngine/Display.h"
#include "../renderEngine/Loader.h"
#include "../models/RawModel.h"
#include "../textures/ModelTexture.h"
#include "../entities/Entity.h"
#include "../entities/Camera.h"
#include "../renderEngine/MasterRenderer.h"
#include "../objLoader/OBJFileLoader.h"
#include "../entities/Player.h"

int main(int argc, char *argv[])
{
	// create display, loader and master renderer
	Display display = Display();
	Loader loader = Loader();
	MasterRenderer renderer;

	// player model
	ModelData dragonData = OBJFileLoader::loadObjModel("res/dragon.obj", loader);
	RawModel dragonRawModel = loader.loadToVAO(dragonData.getVertices(), dragonData.getTexCoords(), dragonData.getNormals(), dragonData.getIndices());
	ModelTexture dragonTexture = ModelTexture(loader.loadTexture("res/blank.png"));
	dragonTexture.setReflectivity(1);
	dragonTexture.setShineDamper(10);
	TexturedModel dragonTexturedModel = TexturedModel(dragonRawModel, dragonTexture);

	// setup the player instance, pass a pointer to the camera object
	std::unique_ptr<Player> player(new Player(dragonTexturedModel, glm::vec3(500,0,500), 0,0,0,1));
	Camera camera = Camera(player.get());

	// trees
	ModelData treeData = OBJFileLoader::loadObjModel("res/lowPolyTree.obj", loader);
	RawModel treeRawModel = loader.loadToVAO(treeData.getVertices(), treeData.getTexCoords(), treeData.getNormals(), treeData.getIndices());
	ModelTexture treeTexture = ModelTexture(loader.loadTexture("res/lowPolyTree.png"));
	TexturedModel treeTexturedModel = TexturedModel(treeRawModel, treeTexture);
	std::vector<Entity> trees;
	for (int i = 0; i < 200; i++){
		Entity tree = Entity(treeTexturedModel, glm::vec3(rand()%600,0,rand()%600), 0,rand()%1000,0,1);
		trees.push_back(tree);
	}

	// grass
	ModelData grassData = OBJFileLoader::loadObjModel("res/grassModel.obj", loader);
	RawModel grassRawModel = loader.loadToVAO(grassData.getVertices(), grassData.getTexCoords(), grassData.getNormals(), grassData.getIndices());
	ModelTexture grassTexture = ModelTexture(loader.loadTexture("res/grassTexture.png"));
	grassTexture.setHasTransparency(true);
	grassTexture.setFakeLight(true);
	TexturedModel grassTexturedModel = TexturedModel(grassRawModel, grassTexture);
	std::vector<Entity> grasses;
	for (int i = 0; i < 200; i++){
		Entity grass = Entity(grassTexturedModel, glm::vec3(rand()%600,0,rand()%600), 0,rand()%1000,0,3);
		grasses.push_back(grass);
	}

	// terrains
	TerrainTexture backgroundTexture = TerrainTexture(loader.loadTexture("res/grass.png"));
	TerrainTexture rTexture = TerrainTexture(loader.loadTexture("res/path.png"));
	TerrainTexture gTexture = TerrainTexture(loader.loadTexture("res/grassFlowers.png"));
	TerrainTexture bTexture = TerrainTexture(loader.loadTexture("res/mud.png"));
	TerrainTexturePack texturePack = TerrainTexturePack(backgroundTexture, rTexture, gTexture, bTexture);
	TerrainTexture blendMap = TerrainTexture(loader.loadTexture("res/blendMap.png"));

	Terrain terrain1 = Terrain(0,0,loader,texturePack, blendMap);
	Terrain terrain2 = Terrain(1,0,loader,texturePack, blendMap);

	Light light = Light(glm::vec3(0,1000,0), glm::vec3(1,1,1));


	// main loop
	while (!glfwWindowShouldClose(display.window)){
		player->move(); // move player first
		camera.move(); // camera position depends on player

		// render terrains
		renderer.processTerrain(terrain1);
		renderer.processTerrain(terrain2);

		// render entities
		for(Entity tree : trees){
			renderer.processEntity(tree);
		}
		for(Entity grass : grasses){
			renderer.processEntity(grass);
		}
		renderer.processEntity(*player);
		renderer.render(light, camera);

		// clear the buffer and fill it with the new render result
		display.update();
	}

	// clean up objects created in the graphics unit
	renderer.cleanUp();
	loader.cleanUp();
	display.close();
	return 0;
}
