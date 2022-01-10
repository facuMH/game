#include "Enemy.h"
#include "AssetsPaths.h"

Enemy createAlien(AssetsManager& am) {
	Texture* alien_texture = am.getTexture(ALIEN.c);
	Animation alien_animation(alien_texture, sf::IntRect(50, 25, 105, 145), Position(100, 100));
	Enemy alien("Alien", Stats(15, 25, 50, 30, 10, 1), alien_animation, MovementType::HORIZONTAL, {20, 20}, 2.0f);
	return alien;
}