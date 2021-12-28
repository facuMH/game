#include "TileMap.h"
#include "AssetsPaths.h"


// Constructor
TileMap::TileMap(AssetsManager& am, std::vector<MapBackground*> textureSheets, const JSONFilePath& designPath) {
	initializeVariables(am);
	loadFromJson(designPath, textureSheets);
}

// Destructor
TileMap::~TileMap() {
	for(int z = 0; z < nLayers; z++) {
		for(int y = 0; y < mapSize.y; y++) {
			for(int x = 0; x < mapSize.x; x++) {
				delete tiles[z][y][x];
			}
		}
	}
}

void TileMap::initializeVariables(AssetsManager& am) {
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
		mapSize.y = layers[z].getSize().x;
		mapSize.x = layers[z].getSize().y;
		if(layers[z].getType() == tson::LayerType::TileLayer) {
			for(int y = 0; y < mapSize.y; y++) {
				tiles[z].resize(mapSize.y, std::vector<Tile*>());
				for(int x = 0; x < mapSize.x; x++) {
					tson::TileObject* tileObj = layers[z].getTileObject(y, x);
					tiles[z][y].push_back(new Tile(tileObj, textureSheets[z]));

					tson::Property* prp_isBlocked = tileObj->getTile()->getProp("isBlocked");
					if(prp_isBlocked != nullptr && prp_isBlocked->getValue<bool>()) {
						tiles[0][y][x]->is_solid = true;
					}

					tson::Property* prp_isDoor = tileObj->getTile()->getProp("door");
					if(prp_isDoor != nullptr && prp_isDoor->getValue<int>() != 0) {
						tiles[0][y][x]->doorNum = prp_isDoor->getValue<int>();
					}
				}
			}
		}
	}
}

bool TileMap::hasNoCollision(Position position) {
	int tilePosX = std::ceil(position.x / TILESIZE);
	int tilePosY = std::ceil(position.y / TILESIZE);
	return !tiles[0][tilePosX][tilePosY]->is_solid && !tiles[0][tilePosX][tilePosY]->is_occupied;
}

void TileMap::setTileOccupation(Position position, bool isOccupied) {
	int tilePosX = std::ceil(position.x / TILESIZE);
	int tilePosY = std::ceil(position.y / TILESIZE);
	tiles[0][tilePosX][tilePosY]->is_occupied = isOccupied;
}

int TileMap::getTileDoorNumber(Position position) {
	int tilePosX = std::ceil(position.x / TILESIZE);
	int tilePosY = std::ceil(position.y / TILESIZE);
	return tiles[0][tilePosX][tilePosY]->doorNum;
}

void TileMap::render(sf::RenderWindow& window) {
	for(int z = 0; z < nLayers; z++) {
		for(int y = 0; y < mapSize.y; y++) {
			for(int x = 0; x < mapSize.x; x++) {
				tiles[z][y][x]->render(window);
			}
		}
	}
}