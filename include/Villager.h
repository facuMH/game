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
			currentDirection = Direction::LEFT;
		} else {
			currentDirection = Direction::DOWN;
		}
		currentPosition = _currentPos;
		startPosition = _currentPos;
		endPosition = _endPosition;
		stepsize = _stepsize;
	}
	// Define an area in which the villager can move
	Position startPosition;
	Position endPosition;
	Position currentPosition;
	MovementType movementType;
	Direction currentDirection;
	float stepsize;

	void setTileOccupation(TileMap* map, bool isOccupied) const { map->setTileOccupation(currentPosition, isOccupied); }

	void move(TileMap* map) {
		setTileOccupation(map, false);
		currentDirection = nextDirection();
		currentPosition = animation.nextVillager(map, stepsize, currentDirection, currentPosition);
		setTileOccupation(map, true);
	};

	Direction nextDirection() const {
		switch(movementType) {
		case MovementType::VERTICAL:
			if(currentDirection == Direction::DOWN) {
				if(currentPosition.y < endPosition.y) {
					return Direction::DOWN;
				} else {
					return Direction::UP;
				}
			} else {
				if(currentPosition.y >= startPosition.y) {
					return Direction::UP;
				} else {
					return Direction::DOWN;
				}
			}
		case MovementType::HORIZONTAL:
			if(currentDirection == Direction::RIGHT) {
				if(currentPosition.x < endPosition.x) {
					return Direction::RIGHT;
				} else {
					return Direction::LEFT;
				}
			} else {
				if(currentPosition.x > startPosition.x) {
					return Direction::LEFT;
				} else {
					return Direction::RIGHT;
				}
			}
		}
	}
};