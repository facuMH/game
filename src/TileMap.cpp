#include <iostream>

#include "TileMap.h"

// Helper function for mapping an iteration counter to a tile from the tile sheet
sf::Vector2i map1Dto2D(int counter) {
	int row = counter / 16;
	int col = counter % 16;
	return {row, col};
}

// Helper function for reading  a level definition into a vector
LevelDesign readLevelDataFromFile(const std::string& inputFile) {
	LevelDesign level = {};
	std::ifstream is(inputFile);
	int x;
	while(is >> x) {
		level.push_back(x);
	}
	return level;
}

// Constructor
TileMap::TileMap() {
	gridSize = 20;
	// The window size fits exactly 32 x 24 tiles of grid size 20
	maxSize.x = 32;
	maxSize.y = 24;
	nLayers = 1; // TODO: later we could have more than 1 layer

	// initialize first rectangle (or tile) position in the upper left corner of the window
	textureRectangle = sf::IntRect(0, 0, gridSize, gridSize);

	// load texture file
	tileTextureSheet.loadFromFile("../assets/tiles/tilesheet.png");

	// load level design
	std::vector<int> levelMap = readLevelDataFromFile("../config/level1.txt");

	int counter = 0;

	// set up 3D vector
	tiles.resize(maxSize.x, TileMapRows());
	for(size_t y = 0; y < maxSize.y; y++) {
		for(size_t x = 0; x < maxSize.x; x++) {
			tiles[x].resize(maxSize.y, TileMapColumns());

			for(size_t z = 0; z < nLayers; z++) {
				tiles[x][y].resize(nLayers, TileLayers());

				// enter tiles only if within bounds, else, do nothing
				if(x < maxSize.x && x >= 0 && y < maxSize.y && y >= 0 && z < nLayers && z >= 0) {
					// store tiles in respective vector position
					sf::Vector2i pos = map1Dto2D(levelMap[counter]);

					// move textureRectangle to specified position in tile sheet to get the correct texture
					textureRectangle.left = (pos.y * gridSize);
					textureRectangle.top = (pos.x * gridSize);

					// create new tile and save at correct position in the 3D array
					tiles[x][y][z].push_back(new Tile(float(x * gridSize), float(y * gridSize), float(gridSize), tileTextureSheet, textureRectangle));
					counter++;
				}
			}
		}
	}
}


TileMap::~TileMap() {
	for(size_t x = 0; x < maxSize.x; x++) {
		for(size_t y = 0; y < maxSize.y; y++) {
			for(size_t z = 0; z < nLayers; z++) {
				delete tiles[x][y][z][0];
			}
		}
	}
}

void TileMap::update() {}

void TileMap::render(sf::RenderTarget& target) {
	for(int x = 0; x < maxSize.x; x++) {
		for(int y = 0; y < maxSize.y; y++) {
			for(int z = 0; z < nLayers; z++) {
				tiles[x][y][z][0]->render(target);
			}
		}
	}
}
