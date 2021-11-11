#include "TileMap.h"
#include <iostream>

TileMap::TileMap()
{
    this->gridSizeF = 50.0f;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);

    this->maxSize.x = 100;
    this->maxSize.y = 100;
    this->nLayers = 2;

    this->tiles.resize(this->maxSize.x, std::vector< std::vector< std::vector<Tile*> > >());
    for (size_t x = 0; x < this->maxSize.x; x++)
    {
        for (size_t y = 0; y < this->maxSize.y; y++)
        {
            this->tiles[x].resize(this->maxSize.y, std::vector< std::vector<Tile*> >());

            for (size_t z = 0; z < this->nLayers; z++)
            {
                this->tiles[x][y].resize(this->nLayers, std::vector<Tile*>());
                if (x < this->maxSize.x && x >= 0 &&
                    y < this->maxSize.y && y >= 0 &&
                    z < this->nLayers && z >= 0) {
                    this->tiles[x][y][z].push_back(new Tile(1.0, 1.0, 50.0));
                }

            }
        }
    }
}

TileMap::~TileMap()
= default;

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget &target)
{
    for (int x = 0; x < this->tiles.size(); x++)
    {
        for (int y = 0; y < x; y++)
        {
            for (int z = 0; z < nLayers; z++)
            {
                this->tiles[x][y][z][0]->render(target);
            }
        }
    }
}