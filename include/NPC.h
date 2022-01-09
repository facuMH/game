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
		if(movementType == MovementType::VERTICAL) {
			if(currentDirection == KeyAction::DOWN) {
				if(currentPosition.y < endPosition.y) {
					return KeyAction::DOWN;
				} else {
					return KeyAction::UP;
				}
			} else {
				if(currentPosition.y >= startPosition.y) {
					return KeyAction::UP;
				} else {
					return KeyAction::DOWN;
				}
			}
		} else {
			if(currentDirection == KeyAction::RIGHT) {
				if(currentPosition.x < endPosition.x) {
					return KeyAction::RIGHT;
				} else {
					return KeyAction::LEFT;
				}
			} else {
				if(currentPosition.x > startPosition.x) {
					return KeyAction::LEFT;
				} else {
					return KeyAction::RIGHT;
				}
			}
		}
	}
};