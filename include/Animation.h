#pragma once

#include <SFML/Graphics.hpp>

#include "definitions.h"

class Animation {
  public:
	sf::Sprite sprite;
	sf::Texture* texture = nullptr;
	sf::IntRect texture_rectangle;
	Interval sprite_interval;

	Animation(){};

	Animation(const sf::Texture* texture, const sf::IntRect& first_animation, const Interval& sprite_interval, const Position& initial) {
		texture = texture;
		texture_rectangle = first_animation;

		this->sprite_interval = sprite_interval;
		sprite.setTexture(*texture);
		sprite.setTextureRect(texture_rectangle);
		sprite.setPosition(initial);
		sprite.setScale({3, 3});
	};

	void set_texture(const sf::Texture* texture) { sprite.setTexture(*texture); }

	void next() {
		texture_rectangle.left = int(texture_rectangle.left + sprite_interval.x) % texture->getSize().x;
		sprite.setTextureRect(texture_rectangle);
	}

	void move(const Position& new_position) { sprite.move(new_position); }

	Position get_position() { return sprite.getPosition(); }

	void set_position(Position pos) { sprite.setPosition(pos); }

	sf::Vector2f get_orientation() { return sprite.getScale(); }

	// TODO: consider taking paramerters to set origin depending on orientation
	void mirror() {
		sprite.setOrigin({0, 0});
		sprite.scale({-1.f, 1.f});
	}

	void mirror(float origin_x) {
		sprite.setOrigin({origin_x, 0});
		sprite.scale({-1.f, 1.f});
	}
};