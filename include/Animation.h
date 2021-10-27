#pragma once

#include <SFML/Graphics.hpp>

using Position = sf::Vector2f;
using Interval = sf::Vector2f;

class Animation {
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect texture_rectangle;
	Interval sprite_interval;

public:
	Animation(const std::string& texture_path, const sf::IntRect& first_animation, const Interval& sprite_interval, const Position& initial) {
		texture.loadFromFile(texture_path);
		texture_rectangle = first_animation;

		this->sprite_interval = sprite_interval;
		sprite.setTexture(texture);
		sprite.setTextureRect(texture_rectangle);
		sprite.setPosition(initial);
	};

	Animation(const Animation& from) {
		sprite = std::move(from.sprite);
		texture = std::move(from.texture);
		texture_rectangle = std::move(from.texture_rectangle);
		sprite_interval = std::move(from.sprite_interval);
	}

	Animation(Animation&& from) {
		sprite = std::move(from.sprite);
		texture = std::move(from.texture);
		texture_rectangle = std::move(from.texture_rectangle);
		sprite_interval = std::move(from.sprite_interval);
	};

	bool set_sexture(const std::string& texture_path) {
		return texture.loadFromFile(texture_path);
	}

	void next() {
		texture_rectangle.left = int(texture_rectangle.left + sprite_interval.x) % texture.getSize().x;
		sprite.setTextureRect(texture_rectangle);
	}

	void move(const Position& new_position) {
		sprite.move(new_position);
	}

	Position get_position() {
		return sprite.getPosition();
	}
};