#include "TileMap.h"

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
        // add empty vector
        this->tiles.emplace_back();

        for (size_t y = 0; y < this->maxSize.y; y++)
        {
            this->tiles[x].resize(this->maxSize.y, std::vector< std::vector<Tile*> >());

            for (size_t z = 0; z < this->nLayers; z++)
            {
                this->tiles[x][y].resize(this->nLayers, std::vector<Tile*>());
            }
        }
    }
}

TileMap::~TileMap()
{

}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget &target)
{
    for (int x = 0; x < this->tiles.size(); x++)
    {
        for (int y = 0; y < x; y++)
        {
            for (int z = 0; y < z; z++)
            {
                Tile tile = reinterpret_cast<const Tile &>(this->tiles[x][y][z]);
                tile.render(target);
            }
        }
    }
}