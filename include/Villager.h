#pragma once

#include <utility>

#include "Animation.h"
#include "Entity.h"
#include "definitions.h"

class Villager : public Entity {
  private:
  public:
	Villager(Animation _animation, MovementType _movementType, Position _currentPos, Position _endPosition,
	    float _stepsize) {
		animation = std::move(_animation);
		movementType = _movementType;
		is_solid = true;
		can_interact = true;

		if(movementType == MovementType::HORIZONTAL) {
			currentDirection = KeyAction::LEFT;
		} else {
			currentDirection = KeyAction::DOWN;
		}
		currentPosition = _currentPos;
		startPosition = _currentPos;
		endPosition = _endPosition;
		stepsize = _stepsize;
	}
	// Define an area in which the villager can move
	Position startPosition;
	Position endPosition;
	MovementType movementType;
	KeyAction currentDirection;
	float stepsize;

	void move(TileMap* map) {
		setTileOccupation(map, false);
		currentDirection = nextDirection();
		currentPosition = animation.next(currentDirection, map, stepsize, currentPosition, nullptr);
		setTileOccupation(map, true);
	};

	KeyAction nextDirection() const {
		if (movementType == MovementType::VERTICAL) {
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
		}
		else {
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