#pragma once

#include "Tile.h"

using Position = sf::Vector2f;
using Interval = sf::Vector2f;
using Name = std::string;

using TileLayers = std::vector<Tile *>;
using TileMapColumns = std::vector<TileLayers>;
using TileMapRows = std::vector<TileMapColumns>;
using TileMapVector = std::vector<TileMapRows>;
class LevelDesign : public std::vector<int> {
  public:
	// Helper function for reading  a level definition into a vector
	bool loadFromFile(const std::string& inputFile) {
		std::ifstream is(inputFile);
		if(!is.is_open()) { return false; }
		int x;
		while(is >> x) {
			push_back(x);
		}
		return true;
	}
};

class MapBackground : public sf::Texture {};
class Texture : public sf::Texture {};

struct Stats
{
    int str = 0;   // Strength
    int dex = 0;   // Dexterity
    int hp = 0;    // Health Points - Life
    int mana = 0;  // Magic Energy
    Stats(const int s, const int d, const int h, const int m) : str(s), dex(d), hp(h), mana(m)
    {}
};

class Character;

using Enemies = std::vector<Character>;
using Party = std::vector<Character>;