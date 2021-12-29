#pragma once

#include <SFML/Graphics.hpp>

#include "TileMap.h"
#include "definitions.h"

class Animation {
  public:
	sf::Sprite sprite;
	Texture* texture = nullptr;
	sf::IntRect texture_rectangle;

	Animation() = default;

	Animation(Texture* newTexture, const sf::IntRect& first_animation, const Position& initial) {
		texture = newTexture;
		texture_rectangle = first_animation;

		sprite.setTexture(*texture);
		sprite.setTextureRect(texture_rectangle);
		sprite.setPosition(initial);
	};

	void set_texture(const sf::Texture* new_texture) { sprite.setTexture(*new_texture); }

	// Helper function for moving the player, getting the new animation texture and moving the view accordingly
	void moveCharacter(const Position& offset, int newLeft, TileMap* map) {
		auto nextPosition = sprite.getPosition() + offset;
		if(map->hasNoCollision(nextPosition)) {
			sprite.move(offset);
		}
		texture_rectangle.left = newLeft;
		texture_rectangle.top = int(texture_rectangle.top + texture_rectangle.height) % 64; // num of bits
		sprite.setTextureRect(texture_rectangle);
	}

	Position next(KeyAction nextDirection, TileMap* map, float stepsize, Position position) {
		Position offset;
		switch(nextDirection) {
		case KeyAction::DOWN:
			offset = {0.0f, stepsize};
			moveCharacter(offset, 0, map);
			break;
		case KeyAction::UP:
			offset = {0.0f, -stepsize};
			moveCharacter(offset, texture_rectangle.width, map);
			break;
		case KeyAction::LEFT:
			offset = {-stepsize, 0.0f};
			moveCharacter({-stepsize, 0.0f}, 2 * texture_rectangle.width, map);
			break;
		case KeyAction::RIGHT:
			offset = {stepsize, 0.0f};
			moveCharacter({stepsize, 0.0f}, 3 * texture_rectangle.width, map);
			break;
		}
		return position + offset;
	}

	void next(const Position offset) {
		texture_rectangle.left = int(offset.x + texture_rectangle.left) % texture->getSize().x;
		texture_rectangle.height = int(offset.y + texture_rectangle.height) % texture->getSize().y;
		sprite.setTextureRect(texture_rectangle);
	}

	void move(const Position& offset) { sprite.move(offset); }

	Position get_position() const { return sprite.getPosition(); }

	void set_position(Position pos) { sprite.setPosition(pos); }
};