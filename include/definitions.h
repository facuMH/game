#pragma once

using Position = sf::Vector2f;
using Interval = sf::Vector2f;
using Name = std::string;

struct Stats {
	int str = 0;   // Strength
	int dex = 0;   // Dexteriry
	int hp = 0;    // Health Points - Life
	int mana = 0;  // Magic Energy
	Stats(const int s, const int d, const int h, const int m) : str(s), dex(d), hp(h), mana(m) {}
};