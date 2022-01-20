#pragma once

class Movement {
  public:
	float stepsize;

	Movement() = default;

	explicit Movement(float _stepsize) {
		stepsize = _stepsize;
	}
	static void setTileOccupation(TileMap* map, Position position, bool isOccupied) {
		map->setTileOccupation(position, isOccupied);
	}

	Position moveCharacter(KeyAction nextDirection, sf::Sprite* sprite, TileMap* map, Position position) const {
		Position offset;
		switch(nextDirection) {
		case KeyAction::DOWN:
			offset = {0.0f, stepsize};
			break;
		case KeyAction::UP:
			offset = {0.0f, -stepsize};
			break;
		case KeyAction::LEFT:
			offset = {-stepsize, 0.0f};
			break;
		case KeyAction::RIGHT:
			offset = {stepsize, 0.0f};
			break;
		}

		auto nextPosition = position + offset;
		if(map->hasNoCollision(nextPosition)) {
			setTileOccupation(map, position, false);
			sprite->move(offset);
			setTileOccupation(map, nextPosition, true);
		}
		return nextPosition;
	}
};