#include "TileMap.h"
#include "AssetsPaths.h"

// Constructor
TileMap::TileMap(AssetsManager& am, std::vector<MapBackground*> textureSheets, const JSONFilePath& designPath) {
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

Position_i TileMap::getTileFromPos(const Position &pos) {
	int tilePosX = std::ceil(pos.x / TILESIZE);
	int tilePosY = std::ceil(pos.y / TILESIZE);
	return {tilePosX, tilePosY};
}

bool TileMap::hasNoCollision(Position position) {
	auto t = getTileFromPos(position);
	return !tiles[0][t.x][t.y]->is_solid && !tiles[0][t.x][t.y]->is_occupied;
}

void TileMap::setTileOccupation(Position position, bool isOccupied) {
	auto t = getTileFromPos(position);
	tiles[0][t.x][t.y]->is_occupied = isOccupied;
}

void TileMap::setAreaOccupation(const Position& position, const Position_i& size, bool isOccupied) {
	for (int i = int(position.x); i < int(position.x + size.x); i++) {
		for (int j = int(position.y); j < int(position.y + size.y); j++) {
			Position tmp = {float(i), float(j)};
			setTileOccupation(tmp, isOccupied);
		}
	}
}

DoorNumber TileMap::getTileDoorNumber(Position position) {
	auto t = getTileFromPos(position);
	return tiles[0][t.x][t.y]->doorNum;
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
std::vector<std::pair<Position, DoorNumber>> TileMap::getHousePositions() {
	std::vector<std::pair<Position, DoorNumber>> positionDoorNumberVector;
	for(int y = 0; y < mapSize.y; y++) {
		for(int x = 0; x < mapSize.x; x++) {
			if(tiles[0][y][x]->doorNum != 0) {
				positionDoorNumberVector.emplace_back(tiles[0][y][x]->get_position(), tiles[0][y][x]->doorNum);
			}
		}
	}
	return positionDoorNumberVector;
}

