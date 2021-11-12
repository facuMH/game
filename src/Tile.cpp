#include "Tile.h"

Tile::Tile(float x, float y, float gridSize)
{
    // x and y are positions
    this->shape.setSize(sf::Vector2(gridSize, gridSize));
    this->shape.setFillColor(sf::Color::Cyan);
}

Tile::~Tile()
= default;

void Tile::update()
{

}

void Tile::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
}

Tile::Tile()
= default;
