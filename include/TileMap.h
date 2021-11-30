#pragma once

#include "AssetsManager.h"
#include "Tile.h"
#include "definitions.h"

class TileMap {
  private:
	// size of one tile
	int gridSize;
	// number of layers per tile position
	int nLayers;
	// max. number of tiles in x and y direction
	sf::Vector2u maxSize;
    // number of visible tiles in x and y direction
    sf::Vector2u visibleFrom;
    // number of visible tiles in x and y direction
    sf::Vector2u visibleTo;
	// for manipulation rectangle-shaped tiles
	sf::IntRect textureRectangle;
	// Concept:
	// We create a matrix of tiles, but each tile itself is a vector of layers
	TileMapVector tiles;
	// set up 3D vector
	void setUpGrid(std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns);

  public:
	TileMap(AssetsManager& am, std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns);
	virtual ~TileMap();
    void initializeVariables(AssetsManager& am);
	void updateLevel(std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns);
	void render(sf::RenderTarget& target);
};