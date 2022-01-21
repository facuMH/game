#pragma once

#include "Movement.h"

class IdleMovement : public Movement {
  public:
	// Define an area in which the NPC can move
	Position startPosition;
	Position endPosition;
	Position currentPosition;
	MovementType movementType;
	KeyAction currentDirection;

	IdleMovement() = default;
	IdleMovement(MovementType _movementType, Position _startPosition, Position _endPosition, float _stepsize)
	    : Movement(_stepsize) {
		movementType = _movementType;
		if(movementType == MovementType::HORIZONTAL) {
			currentDirection = KeyAction::LEFT;
		} else {
			currentDirection = KeyAction::DOWN;
		}
		startPosition = _startPosition;
		endPosition = _endPosition;
		currentPosition = _startPosition;
	};

	virtual ~IdleMovement() = default;

	void move(Animation* animation, TileMap* map) {
		setTileOccupation(map, animation->get_position(), false);
		animation->next(nextDirection());
		currentDirection = nextDirection();
		currentPosition = moveCharacter(currentDirection, &animation->sprite, map, animation->get_position());
		setTileOccupation(map, animation->get_position(), true);
	}

	KeyAction nextDirection() const {
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