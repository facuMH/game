#pragma once

#include <unordered_map>

#include <SFML\Graphics.hpp>

#include "Button.h"
#include "Tile.h"

using Position = sf::Vector2f;
using Position_i = sf::Vector2i;
using Interval = sf::Vector2f;
using Name = std::string;

using TileLayers = std::vector<Tile*>;
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

using Buttons = std::vector<Button>;
using KeyList = std::unordered_map<std::string, int>;

struct Stats {
	int str = 0;  // Strength
	int dex = 0;  // Dexteriry
	int hp = 0;   // Health Points - Life
	int mana = 0; // Magic Energy
	Stats(const int s, const int d, const int h, const int m) : str(s), dex(d), hp(h), mana(m) {}
};

const sf::Color GREY = sf::Color(70, 70, 70, 200);
const sf::Color LIGHTGREY = sf::Color(150, 150, 150, 255);
const sf::Color BLACK = sf::Color(20, 20, 20, 200);

enum class StateAction { NONE, START_GAME, START_COMBAT, EXIT_COMBAT, EXIT_GAME };