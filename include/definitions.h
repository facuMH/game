#pragma once

#include "Tile.h"

using Position = sf::Vector2f;
using Interval = sf::Vector2f;
using Name = std::string;

using TileLayers = std::vector<Tile *>;
using TileMapColumns = std::vector<TileLayers>;
using TileMapRows = std::vector<TileMapColumns>;
using TileMapVector = std::vector<TileMapRows>;
using LevelDesign = std::vector<int>;

class MapBackground : public sf::Texture {};
class Texture : public sf::Texture {};

struct Stats {
	int str = 0;  // Strength
	int dex = 0;  // Dexteriry
	int hp = 0;   // Health Points - Life
	int mana = 0; // Magic Energy
	Stats(const int s, const int d, const int h, const int m) : str(s), dex(d), hp(h), mana(m) {}
};
