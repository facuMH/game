#pragma once

#include "AssetsManager.h"
#include "Tile.h"
#include "definitions.h"

class TileMap {
  private:
	// size of one tile
	int gridSize = 20;
	// number of layers per tile position
	int nLayers;
	// max. number of tiles in x and y direction
	sf::Vector2u maxSize;
    // number of visible tiles in x and y direction
    sf::Vector2u visibleFrom;
    // number of visible tiles in x and y direction
    sf::Vector2u visibleTo;
	// holds the texture sheet loaded from file
	MapBackground* tileTextureSheet;
	// for manipulation rectangle-shaped tiles
	sf::IntRect textureRectangle;
	// Concept:
	// We create a matrix of tiles, but each tile itself is a vector
	TileMapVector tiles;

  public:
	explicit TileMap(AssetsManager& am);

	virtual ~TileMap();

	void update(sf::Vector2f playerPos);

	void render(sf::RenderTarget& target);
};