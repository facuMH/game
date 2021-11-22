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

		sprite_interval = sprite_interval;
		sprite.setTexture(*texture);
		sprite.setTextureRect(texture_rectangle);
		sprite.setPosition(initial);
		sprite.setScale({2, 2});
	};

	void set_texture(const sf::Texture* new_texture) { sprite.setTexture(*texture); }

	void next() {
		if(texture != nullptr) {
			texture_rectangle.left = int(texture_rectangle.left + sprite_interval.x) % texture->getSize().x;
			sprite.setTextureRect(texture_rectangle);
		}
	}

	void move(const Position& offset) { sprite.move(offset); }

	Position get_position() { return sprite.getPosition(); }

	void set_position(Position pos) { sprite.setPosition(pos); }

	sf::Vector2f get_orientation() { return sprite.getScale(); }

	// TODO: consider taking parameters to set origin depending on orientation
	void mirror() {
		sprite.setOrigin({0, 0});
		sprite.scale({-1.f, 1.f});
	}

	void mirror(float origin_x) {
		sprite.setOrigin({origin_x, 0});
		sprite.scale({-1.f, 1.f});
	}
};