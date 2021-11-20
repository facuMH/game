#include "Tile.h"

Tile::Tile(float xPos, float yPos, float gridSize, const sf::Texture &texture, sf::IntRect rect)
{
    this->shape.setSize(sf::Vector2(gridSize, gridSize));
    this->shape.setPosition(xPos, yPos);
    this->shape.setTexture(&texture);

    this->shape.setTextureRect(rect);
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
