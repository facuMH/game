#include "Tile.h"

Tile::Tile(float xPos, float yPos, float gridSize, const sf::Texture* texture, sf::IntRect rect) {
	shape.setSize(sf::Vector2(gridSize, gridSize));
	shape.setPosition(xPos, yPos);
	shape.setTexture(texture);

	shape.setTextureRect(rect);
}

Tile::Tile(tson::TileObject *tileObject, MapBackground* textureSheet) {
    auto tileSize = tileObject->getTile()->getTileSize();
	shape.setSize(sf::Vector2(float(tileSize.x), float(tileSize.y)));
	auto tilePos = tileObject->getPosition();
	shape.setPosition(tilePos.x, tilePos.y);
	auto tileRect = tileObject->getDrawingRect();
	sf::IntRect intRect = sf::IntRect(tileRect.x, tileRect.y, tileRect.height, tileRect.width);
	shape.setTextureRect(intRect);
	shape.setTexture(textureSheet);
}

Tile::~Tile() = default;

void Tile::update() {}

void Tile::render(sf::RenderTarget& target) {
	target.draw(shape);
}

Tile::Tile() = default;
