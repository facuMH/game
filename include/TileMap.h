#pragma once

#include "Tile.h"
#include "definitions.h"

class TileMap
{
private:
    // size of one tile
    int gridSize = 20;
    // number of layers per tile position
    int nLayers;
    // max. number of tiles in x and y direction
    sf::Vector2u maxSize;
    // holds the texture sheet loaded from file
    sf::Texture tileTextureSheet;
    // for manipulation rectangle-shaped tiles
    sf::IntRect textureRectangle;
    // Concept:
    // We create a matrix of tiles, but each tile itself is a vector
    TileMapVector tiles;

public:
    TileMap();

    virtual ~TileMap();

    void update();

    void render(sf::RenderTarget &target);
};