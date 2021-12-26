#pragma once

#include "AssetsManager.h"
#include "Tile.h"
#include "definitions.h"

#include "tileson.hpp"

class TileMap {
  private:
	// number of layers per tile position
	int nLayers;
	// max. number of tiles in x and y direction
	sf::Vector2u maxSize;
	// Tiles are saved in a matrix, but each tile itself is a vector of layers
	std::vector<std::vector<std::vector<Tile*>>> tiles;

  public:
	TileMap(AssetsManager& am, std::vector<MapBackground*> textureSheets, const JSONFilePath& designPath);
	virtual ~TileMap();

	void initializeVariables(AssetsManager& am);
	void loadFromJson(const std::string& path, std::vector<MapBackground*> textureSheets);
	bool hasNoCollision(Position position);
	void setTileOccupation(Position position, bool isOccupied);
	void render(sf::RenderWindow& window);
};