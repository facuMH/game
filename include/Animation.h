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

	void next(KeyAction nextDirection) {
		int newLeft = 0;
		switch(nextDirection) {
		case KeyAction::DOWN: newLeft = 0; break;
		case KeyAction::UP: newLeft = texture_rectangle.width; break;
		case KeyAction::LEFT: newLeft = 2 * texture_rectangle.width; break;
		case KeyAction::RIGHT: newLeft = 3 * texture_rectangle.width; break;
		}
		texture_rectangle.left = newLeft;
		texture_rectangle.top = int(texture_rectangle.top + texture_rectangle.height) % 64; // num of bits
		sprite.setTextureRect(texture_rectangle);
	}

	void move(const Position& offset) { sprite.move(offset); }

	Position get_position() const { return sprite.getPosition(); }

	void set_position(Position pos) { sprite.setPosition(pos); }
};