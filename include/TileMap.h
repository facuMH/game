#pragma once

#include "AssetsManager.h"
#include "Tile.h"
#include "definitions.h"

#include "../libs/tileson.hpp"

class TileMap {
  private:
	// number of layers per tile position
	int nLayers;
	// max. number of tiles in x and y direction
	sf::Vector2u maxSize;
	// Concept:
	// We create a matrix of tiles, but each tile itself is a vector of layers
	std::vector<std::vector<std::vector<Tile*>>> tiles;
	// a matrix that shows which tiles are blocked
	std::vector<std::vector<bool>> blockMask;

  public:
	TileMap(AssetsManager& am, std::vector<MapBackground*> textureSheets, const JSONFilePath& designPath);
	virtual ~TileMap();
	void initializeVariables(AssetsManager& am);
	bool hasCollision(sf::Vector2i position);
	void render(sf::RenderWindow& window);
	void loadFromJson(const std::string& path, std::vector<MapBackground*> textureSheets);
};