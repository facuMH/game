#include "TileMap.h"
#include "AssetsPaths.h"


// Helper function for mapping an iteration counter to a tile from the tile sheet
sf::Vector2i map1Dto2D(int counter) {
	int row = counter / 16;
	int col = counter % 16;
	return {row, col};
}

void TileMap::initializeVariables(AssetsManager& am) {
	gridSize = 16;
	maxSize.x = 100;
	maxSize.y = 100;

	// bounds for rendering only those tiles that are in visible range
	visibleFrom.x = 0;
	visibleTo.y = 0;
	visibleTo.x = 32;
	visibleTo.y = 24;
	nLayers = 2;

	// initialize first rectangle (or tile) position in the upper left corner of the window
	textureRectangle = sf::IntRect(0, 0, gridSize, gridSize);
}

void TileMap::setUpGrid(std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns) {
	// set up 3D vector
	int counter = 0;
	tiles.resize(maxSize.x, TileMapRows());
	for(size_t y = 0; y < maxSize.y; y++) {
		for(size_t x = 0; x < maxSize.x; x++) {
			tiles[x].resize(maxSize.y, TileMapColumns());

			for(size_t z = 0; z < nLayers; z++) {
				tiles[x][y].resize(nLayers, TileLayers());

				// enter tiles only if within bounds, else, do nothing
				if(x < maxSize.x && x >= 0 && y < maxSize.y && y >= 0 && z < nLayers && z >= 0) {
					// store tiles in respective vector position
					sf::Vector2i pos = map1Dto2D(levelDesigns[z]->at(y).at(x));

					// move textureRectangle to specified position in tile sheet to get the correct texture
					textureRectangle.left = (pos.y * gridSize);
					textureRectangle.top = (pos.x * gridSize);

					// create new tile and save at correct position in the 3D array
					tiles[x][y][z].push_back(new Tile(float(x * gridSize), float(y * gridSize), float(gridSize), textureSheets[z], textureRectangle));
				}
			}
		}
	}
}

// Constructor
TileMap::TileMap(AssetsManager& am, std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns) {
	initializeVariables(am);
	nLayers = levelDesigns.size();
	// load level design
	setUpGrid(textureSheets, levelDesigns);
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

void TileMap::updateLevel(std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns) {
	setUpGrid(textureSheets, levelDesigns);
}

void TileMap::render(sf::RenderTarget& target) {
	for(int x = 0; x < maxSize.x; x++) {
		for(int y = 0; y < maxSize.y; y++) {
			for(int z = 0; z < nLayers; z++) {
				tiles[x][y][z][0]->render(target);
			}
		}
	}
}
