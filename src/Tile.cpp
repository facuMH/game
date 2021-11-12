#include "Tile.h"

Tile::Tile(float xPos, float yPos, float gridSize, sf::Texture &texture)
{
    this->shape.setSize(sf::Vector2(gridSize, gridSize));
    this->shape.setFillColor(sf::Color::Cyan);
    this->shape.setPosition(xPos, yPos);
    this->shape.setTexture(&texture);
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