#include "TileMap.h"
#include "AssetsPaths.h"
#include "tileson.hpp"

// Helper function for mapping an iteration counter to a tile from the tile sheet
sf::Vector2i map1Dto2D(int counter) {
	int row = counter / 16;
	int col = counter % 16;
	return {row, col};
}

void TileMap::initializeVariables(AssetsManager& am) {
	gridSize = 16;
	maxSize.x = 50;
	maxSize.y = 50;

	// bounds for rendering only those tiles that are in visible range
	visibleFrom.x = 0;
	visibleTo.y = 0;
	visibleTo.x = 32;
	visibleTo.y = 24;
	nLayers = 3;

	// initialize first rectangle (or tile) position in the upper left corner of the window
	textureRectangle = sf::IntRect(0, 0, gridSize, gridSize);
}

void TileMap::loadFromJson(const std::string& path, std::vector<MapBackground*> textureSheets) {
	std::cout << path << std::endl;
	tson::Tileson t;
	std::unique_ptr<tson::Map> map = t.parse(fs::path(path));
	auto tilesets = map->getTilesets();
	if(map->getStatus() != tson::ParseStatus::OK) {
		std::cout << "Parse error" << std::endl;
	}
	std::vector<tson::Layer> layers = map->getLayers();
	tiles2.resize(layers.size(), std::vector<std::vector<std::vector<Tile*>>>());
	for(int z = 0; z < 1; z++) {
		tson::Vector2 size = layers[z].getSize();
		if(layers[z].getType() == tson::LayerType::TileLayer) {
			for(int y = 0; y < size.y; y++) {
				tiles2[z].resize(size.y, std::vector<std::vector<Tile*>>());
				for(int x = 0; x < size.x; x++) {
					tiles2[z][y].resize(size.x, std::vector<Tile*>());
					tson::TileObject* tileObj = layers[z].getTileObject(x, y);
					assert(tileObj != nullptr);
					tiles2[z][y][x].push_back(new Tile(tileObj, textureSheets[z]));
				}
			}
		}
	}
}

//void TileMap::setUpGrid(std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns) {
//	// set up 3D vector
//	int counter = 0;
/*	tiles.resize(maxSize.x, TileMapRows());
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
}*/

// Constructor
TileMap::TileMap(AssetsManager& am, std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns) {
	initializeVariables(am);
	// nLayers = levelDesigns.size();
	// load level design
	// setUpGrid(textureSheets, levelDesigns);

	loadFromJson("../assets/tiles/map1.json", textureSheets);
}

TileMap::~TileMap() {
	for(size_t x = 0; x < maxSize.x; x++) {
		for(size_t y = 0; y < maxSize.y; y++) {
			for(size_t z = 0; z < nLayers; z++) {
				delete tiles2[z][y][x][0];
			}
		}
	}
}

void TileMap::render(sf::RenderTarget& target) {
	for(int z = 0; z < nLayers; z++) {
		for(int y = 0; y < maxSize.y; y++) {
			for(int x = 0; x < maxSize.x; x++) {
				tiles2[z][y][x][0]->render(target);
			}
		}
	}
}
