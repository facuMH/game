#pragma once

#include <SFML/Graphics.hpp>

#include "definitions.h"

class Animation {
  public:
	sf::Sprite sprite;
	Texture* texture = nullptr;
	sf::IntRect texture_rectangle;
	Interval sprite_interval;

	Animation() = default;

	Animation(Texture* newTexture, const sf::IntRect& first_animation, const Interval& new_sprite_interval, const Position& initial) {
		texture = newTexture;
		texture_rectangle = first_animation;

		sprite_interval = new_sprite_interval;
		sprite.setTexture(*texture);
		sprite.setTextureRect(texture_rectangle);
		sprite.setPosition(initial);
	};

	void set_texture(const sf::Texture* new_texture) { sprite.setTexture(*new_texture); }

	void next(KeyAction keyAction, sf::View* view, float stepsize) {
		switch(keyAction) {
		case KeyAction::DOWN:
			sprite.move({0.0f, stepsize});
			view->setCenter(sprite.getPosition());
			texture_rectangle.left = 0;
			break;
		case KeyAction::UP:
			sprite.move({0.0f, -stepsize});
			view->setCenter(sprite.getPosition());
			texture_rectangle.left = texture_rectangle.width;
			break;
		case KeyAction::LEFT:
			sprite.move({-stepsize, 0.0f});
			view->setCenter(sprite.getPosition());
			texture_rectangle.left = 2 * texture_rectangle.width;
			break;
		case KeyAction::RIGHT:
			sprite.move({stepsize, 0.0f});
			view->setCenter(sprite.getPosition());
			texture_rectangle.left = 3 * texture_rectangle.width;
			break;
		default: break;
		}
		texture_rectangle.top = int(texture_rectangle.top + texture_rectangle.height) % 64; // num of bits
		sprite.setTextureRect(texture_rectangle);
	}

	void move(const Position& offset) { sprite.move(offset); }

	Position get_position() { return sprite.getPosition(); }

	void set_position(Position pos) { sprite.setPosition(pos); }
};