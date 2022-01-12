#pragma once

class NPC : public virtual Entity {
  public:
	// Define an area in which the villager can move
	Position startPosition;
	Position endPosition;
	MovementType movementType;
	KeyAction currentDirection;
	float stepsize;

	NPC() = default;
	NPC(MovementType _movementType, Position _endPosition, float _stepsize) {
		movementType = _movementType;
		if(movementType == MovementType::HORIZONTAL) {
			currentDirection = KeyAction::LEFT;
		} else {
			currentDirection = KeyAction::DOWN;
		}
		startPosition = animation.get_position();
		endPosition = _endPosition;
		stepsize = _stepsize;
	};

	virtual ~NPC() = default;

	void move(TileMap* map) {
		setTileOccupation(map, false);
		currentDirection = nextDirection();
		animation.next(currentDirection, map, stepsize, animation.get_position());
		setTileOccupation(map, true);
	};

	KeyAction nextDirection() const {
		Position currentPosition = animation.get_position();
		KeyAction nextDirection = KeyAction::NONE;
		if(movementType == MovementType::VERTICAL) {
			switch(currentDirection) {
			case KeyAction::DOWN:
				if(currentPosition.y < endPosition.y) {
					nextDirection = KeyAction::DOWN;
				} else {
					nextDirection = KeyAction::UP;
				}
				break;
			case KeyAction::UP:
				if(currentPosition.y >= startPosition.y) {
					nextDirection = KeyAction::UP;
				} else {
					nextDirection = KeyAction::DOWN;
				}
				break;
			default: break;
			}
		} else {
			switch(currentDirection) {
			case KeyAction::RIGHT:
				if(currentPosition.x < endPosition.x) {
					nextDirection = KeyAction::RIGHT;
				} else {
					nextDirection = KeyAction::LEFT;
				}
				break;
			case KeyAction::LEFT:
				if(currentPosition.x > startPosition.x) {
					nextDirection = KeyAction::LEFT;
				} else {
					nextDirection = KeyAction::RIGHT;
				}
				break;
			default: break;
			}
		}
		return nextDirection;
	}
};