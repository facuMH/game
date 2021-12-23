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
		for(int y = 0; y < maxSize.y; y++) {
			for(int x = 0; x < maxSize.x; x++) {
				delete tiles[z][y][x];
			}
		}
	}
}

void TileMap::initializeVariables(AssetsManager& am) {
	maxSize.x = 50;
	maxSize.y = 50;
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
						tiles[0][y][x]->is_solid = true;
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

void TileMap::occupyTile(Position position) {
	int tilePosX = std::ceil(position.x / TILESIZE);
	int tilePosY = std::ceil(position.y / TILESIZE);
	tiles[0][tilePosX][tilePosY]->is_occupied = true;
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
