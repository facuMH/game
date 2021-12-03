#pragma once

#include <unordered_map>

#include <SFML/Graphics.hpp>

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
class Design : public std::vector<std::vector<int>> {
  public:
	// Helper function for reading a level definition from a CSV file into a vector
	bool loadFromFile(const std::string& inputFile) {
		std::ifstream in;
		in.open(inputFile);

		if(!in.is_open()) {
			return false;
		}
		std::string line;
		while(getline(in, line)) {
			std::stringstream sep(line);
			std::string cell;

			push_back(std::vector<int>());

			while(getline(sep, cell, ',')) {
				back().push_back(stoi(cell));
			}
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
	int dex = 0;  // Dexterity
	int hp = 0;   // Health Points - Life
	int mana = 0; // Magic Energy
	Stats(const int s, const int d, const int h, const int m) : str(s), dex(d), hp(h), mana(m) {}
};

const sf::Color GREY = sf::Color(70, 70, 70, 200);
const sf::Color LIGHTGREY = sf::Color(150, 150, 150, 255);
const sf::Color BLACK = sf::Color(20, 20, 20, 200);

enum class StateAction { NONE, START_GAME, START_COMBAT, EXIT_COMBAT, EXIT_GAME };

class Character;
using Enemies = std::vector<Character>;
using Party = std::vector<Character>;
using CombatText = std::unordered_map<Name, sf::Text>;