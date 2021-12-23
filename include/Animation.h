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
	void moveCharacterAndView(const Position& offset, int newTextureRect, sf::View* view, TileMap* map) {
		auto nextPosition = sprite.getPosition() + offset;
		if(map->hasNoCollision(nextPosition)) {
			sprite.move(offset);
			if(view != nullptr) {
				view->setCenter(sprite.getPosition());
			}
		}
		texture_rectangle.left = newTextureRect;
		texture_rectangle.top = int(texture_rectangle.top + texture_rectangle.height) % 64; // num of bits
		sprite.setTextureRect(texture_rectangle);
	}

	Position next(KeyAction nextDirection, TileMap* map, float stepsize, Position position, sf::View* view) {
		Position offset;
		switch(nextDirection) {
		case KeyAction::UP:
			offset = {0.0f, -stepsize};
			moveCharacterAndView(offset, texture_rectangle.width, view, map);
			break;
		case KeyAction::DOWN:
			offset = {0.0f, stepsize};
			moveCharacterAndView(offset, 0, view, map);
			break;
		case KeyAction::RIGHT:
			offset = {stepsize, 0.0f};
			moveCharacterAndView({stepsize, 0.0f}, 3 * texture_rectangle.width, view, map);
			break;
		case KeyAction::LEFT:
			offset = {-stepsize, 0.0f};
			moveCharacterAndView({-stepsize, 0.0f}, 2 * texture_rectangle.width, view, map);
			break;
		}
		return position + offset;
	}

	void move(const Position& offset) { sprite.move(offset); }

	Position get_position() { return sprite.getPosition(); }

	void set_position(Position pos) { sprite.setPosition(pos); }
};