#include "TileMap.h"
#include <iostream>

// Helper function for mapping an iteration counter to a tile from the tile sheet
sf::Vector2i map1Dto2D(int counter)
{
    int row = counter / 16;
    int col = counter % 16;
    return {row, col};
}

// Helper function for reading  a level definition into a vector
std::vector<int> readLevelDataFromFile(const std::string &inputFile)
{
    std::vector<int> level = {};
    std::ifstream is(inputFile);
    int x;
    while (is >> x)
    {
        level.push_back(x);
    }
    return level;
}

// Constructor
TileMap::TileMap()
{
    this->gridSizeF = 20.0f;
    this->gridSizeI = static_cast<unsigned>(this->gridSizeF);

    this->maxSize.x = 32;
    this->maxSize.y = 24;
    this->nLayers = 1; // TODO: later we could have more than 1 layer

    this->rect = sf::IntRect(0, 0, this->gridSizeI, this->gridSizeI);

    // load texture file
    this->tileTextureSheet.loadFromFile("../assets/tiles/tilesheet.png");

    // load level design
    std::vector<int> levelMap = readLevelDataFromFile("../config/level1.txt");

    int counter = 0;

    // set up 3D vector
    this->tiles.resize(this->maxSize.x, std::vector<std::vector<std::vector<Tile *> > >());
    for (size_t y = 0; y < this->maxSize.y; y++)
    {

            for (size_t x = 0; x < this->maxSize.x; x++)
        {
            this->tiles[x].resize(this->maxSize.y, std::vector<std::vector<Tile *> >());

            for (size_t z = 0; z < this->nLayers; z++)
            {
                this->tiles[x][y].resize(this->nLayers, std::vector<Tile *>());

                if (x < this->maxSize.x && x >= 0 &&
                    y < this->maxSize.y && y >= 0 &&
                    z < this->nLayers && z >= 0)
                {
                    // store tiles in respective vector position
                    sf::Vector2i pos = map1Dto2D(levelMap[counter]);

                    // move rect to specified position in tile sheet to get the correct texture
                    this->rect.left = (pos.y * gridSizeI);
                    this->rect.top = (pos.x * gridSizeI);

                    // create new tile and save at correct position in the 3D array
                    this->tiles[x][y][z].push_back(
                            new Tile(x * gridSizeF, y * gridSizeF, gridSizeF, this->tileTextureSheet, this->rect));
                    counter++;
                }
            }
        }
    }
}


TileMap::~TileMap()
{
    for (size_t x = 0; x < this->maxSize.x; x++)
    {
        for (size_t y = 0; y < this->maxSize.y; y++)
        {
            for (size_t z = 0; z < this->nLayers; z++)
            {
                delete this->tiles[x][y][z][0];
            }
        }
    }
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget &target)
{
    for (int x = 0; x < this->maxSize.x; x++)
    {
        for (int y = 0; y < this->maxSize.y; y++)
        {
            for (int z = 0; z < nLayers; z++)
            {
                this->tiles[x][y][z][0]->render(target);
            }
        }
    }
}
