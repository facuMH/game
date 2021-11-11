#pragma once

#include "Tile.h"

class TileMap
{
private:
    unsigned gridSizeU;
    float gridSizeF;
    unsigned nLayers;
    sf::Vector2u maxSize;
    // Concept:
    // We create a matrix of tiles, but each tile itself is a vector
    std::vector< std::vector< std::vector< std::vector<Tile*> > > > tiles;
public:
    TileMap();

    virtual ~TileMap();

    void update();

    void render(sf::RenderTarget &target);
};