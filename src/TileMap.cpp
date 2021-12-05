#include "TileMap.h"
#include "AssetsPaths.h"
#include "tileson.hpp"

void TileMap::initializeVariables(AssetsManager& am) {
	gridSize = 16;
	maxSize.x = 50;
	maxSize.y = 50;

	// bounds for rendering only those tiles that are in visible range
	visibleFrom.x = 0;
	visibleTo.y = 0;
	visibleTo.x = 32;
	visibleTo.y = 24;

	// initialize first rectangle (or tile) position in the upper left corner of the window
	textureRectangle = sf::IntRect(0, 0, gridSize, gridSize);
}

void TileMap::loadFromJson(const std::string& path, std::vector<MapBackground*> textureSheets) {
	tson::Tileson t;
	std::unique_ptr<tson::Map> map = t.parse(fs::path(path));

	if(map->getStatus() != tson::ParseStatus::OK) {
		std::cout << "Parse error" << std::endl;
	}
	std::vector<tson::Layer> layers = map->getLayers();
	nLayers = layers.size();
	tiles.resize(nLayers, std::vector<std::vector<std::vector<Tile*>>>());
	for(int z = 0; z < nLayers; z++) {
		tson::Vector2 size = layers[z].getSize();
		if(layers[z].getType() == tson::LayerType::TileLayer) {
			for(int y = 0; y < size.y; y++) {
				tiles[z].resize(size.y, std::vector<std::vector<Tile*>>());
				for(int x = 0; x < size.x; x++) {
					tiles[z][y].resize(size.x, std::vector<Tile*>());
					tson::TileObject* tileObj = layers[z].getTileObject(y, x);
					tiles[z][y][x].push_back(new Tile(tileObj, textureSheets[z]));
				}
			}
		}
	}
}

// Constructor
TileMap::TileMap(AssetsManager& am, std::vector<MapBackground*> textureSheets, JSONFilePath designPath) {
	initializeVariables(am);
	// nLayers = levelDesigns.size();
	// load level design
	// setUpGrid(textureSheets, levelDesigns);

	loadFromJson(designPath, textureSheets);
}

TileMap::~TileMap() {
	for(size_t x = 0; x < maxSize.x; x++) {
		for(size_t y = 0; y < maxSize.y; y++) {
			for(size_t z = 0; z < nLayers; z++) {
				delete tiles[z][y][x][0];
			}
		}
	}
}

void TileMap::render(sf::RenderTarget& target) {
	for(int z = 0; z < nLayers; z++) {
		for(int y = 0; y < maxSize.y; y++) {
			for(int x = 0; x < maxSize.x; x++) {
				tiles[z][y][x][0]->render(target);
			}
		}
	}
}
