#include "Tile.h"

Tile::Tile(tson::TileObject* tileObject, MapBackground* textureSheet) {
	auto tileSize = tileObject->getTile()->getTileSize();
	auto tilePos = tileObject->getPosition();
	auto tileRect = tileObject->getDrawingRect();
	sf::IntRect intRect = sf::IntRect(tileRect.x, tileRect.y, tileRect.height, tileRect.width);

	shape.setSize(sf::Vector2(float(tileSize.x), float(tileSize.y)));
	shape.setPosition(tilePos.x, tilePos.y);
	shape.setTexture(textureSheet);
	shape.setTextureRect(intRect);
	is_solid = false;
	doorNum = 0;
}

Position Tile::get_position() {
	return shape.getPosition();
}

Tile::~Tile() = default;

void Tile::update() {}

void Tile::render(sf::RenderWindow& window) {
	window.draw(shape);
}
