#include "Tile.h"

Tile::Tile(float xPos, float yPos, float gridSize, const sf::Texture* texture, sf::IntRect rect) {
	shape.setSize(sf::Vector2(gridSize, gridSize));
	shape.setPosition(xPos, yPos);
	shape.setTexture(texture);

	shape.setTextureRect(rect);
}

Tile::~Tile() = default;

void Tile::update() {}

void Tile::render(sf::RenderTarget& target) {
	target.draw(shape);
}

Tile::Tile() = default;
