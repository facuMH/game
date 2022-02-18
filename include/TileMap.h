#pragma once

#include "Tile.h"
#include "definitions.h"
#include "managers/AssetsManager.h"

#include "tileson.hpp"


class TileMap {
  private:
	int nLayers;          // number of layers per tile position
	sf::Vector2u mapSize; // max. number of tiles in x and y direction
	std::vector<std::vector<std::vector<Tile*>>>
	    tiles; // Tiles are saved in a 2D vector. Each tile position itself is a vector of layers

  public:
	TileMap(AssetsManager& am, std::vector<MapBackground*> textureSheets, const JSONFilePath& designPath);
	virtual ~TileMap();

	void loadFromJson(const std::string& path, std::vector<MapBackground*> textureSheets);
	bool hasNoCollision(Position position);
	DoorNumber getTileDoorNumber(Position position);
	std::vector<std::pair<Position, DoorNumber>> getHousePositions();
	void setTileOccupation(Position position, bool isOccupied);
	void render(sf::RenderWindow& window);
	Position_i getTileFromPos(const Position& pos);
};