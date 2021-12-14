#include "TileMap.h"
#include "AssetsPaths.h"
#include "tileson.hpp"

#define TILESIZE 16

// Constructor
TileMap::TileMap(AssetsManager& am, std::vector<MapBackground*> textureSheets, const JSONFilePath& designPath) {
	initializeVariables(am);
	loadFromJson(designPath, textureSheets);
}

void TileMap::initializeVariables(AssetsManager& am) {
	maxSize.x = 50;
	maxSize.y = 50;

	// bounds for rendering only those tiles that are in visible range
	visibleFrom.x = 0;
	visibleTo.y = 0;
	visibleTo.x = 32;
	visibleTo.y = 24;

	// initialize matrix for collision detection
	blockMask.resize(maxSize.x, std::vector<bool>(maxSize.y, false));
}

void TileMap::loadFromJson(const std::string& path, std::vector<MapBackground*> textureSheets) {
	tson::Tileson t;
	std::unique_ptr<tson::Map> map = t.parse(fs::path(path));

	if(map->getStatus() != tson::ParseStatus::OK) {
		std::cout << "Parse error" << std::endl;
	}
	std::vector<tson::Layer> layers = map->getLayers();
	nLayers = layers.size();
	tiles.resize(nLayers, std::vector<std::vector<Tile*>>());
	for(int z = 0; z < nLayers; z++) {
		tson::Vector2 size = layers[z].getSize();
		if(layers[z].getType() == tson::LayerType::TileLayer) {
			for(int y = 0; y < size.y; y++) {
				tiles[z].resize(size.y, std::vector<Tile*>());
				for(int x = 0; x < size.x; x++) {
					tson::TileObject* tileObj = layers[z].getTileObject(y, x);
					tiles[z][y].push_back(new Tile(tileObj, textureSheets[z]));
					tson::Property* prp = tileObj->getTile()->getProp("isBlocked");
					if(prp != nullptr && prp->getValue<bool>()) {
						blockMask[y][x] = true;
					}
				}
			}
		}
	}
}

TileMap::~TileMap() {
	for(int z = 0; z < nLayers; z++) {
		for(int y = 0; y < maxSize.y; y++) {
			for(int x = 0; x < maxSize.x; x++) {
				delete tiles[z][y][x];
			}
		}
	}
}

void TileMap::render(sf::RenderWindow& window) {
	for(int z = 0; z < nLayers; z++) {
		for(int y = 0; y < maxSize.y; y++) {
			for(int x = 0; x < maxSize.x; x++) {
				tiles[z][y][x]->render(window);
			}
		}
	}
}


bool TileMap::hasCollision(sf::Vector2i position) {
	int tilePosX = position.x / TILESIZE;
	int tilePosY = position.y / TILESIZE;
	return blockMask[tilePosX][tilePosY];
}
