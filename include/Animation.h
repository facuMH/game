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

	// Helper function for moving the player, getting the new animation texture and moving the view accordingly
	void movePlayerAndView(const sf::Vector2<float> &offset, sf::View *view, int newTextureRect) {
		sprite.move(offset);
		texture_rectangle.left = newTextureRect;
		view->setCenter(sprite.getPosition());
	}

	void next(KeyAction keyAction, sf::View* view, float stepsize) {
		switch(keyAction) {
		case KeyAction::DOWN: movePlayerAndView({0.0f, stepsize}, view, 0);
			break;
		case KeyAction::UP: movePlayerAndView({0.0f, -stepsize}, view, texture_rectangle.width);
			break;
		case KeyAction::LEFT: movePlayerAndView({-stepsize, 0.0f}, view, 2 * texture_rectangle.width);
			break;
		case KeyAction::RIGHT: movePlayerAndView({stepsize, 0.0f}, view, 3 * texture_rectangle.width);
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