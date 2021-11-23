#pragma once

#include <iostream>
#include "Tile.h"

using Position = sf::Vector2f;
using Interval = sf::Vector2f;
using Name = std::string;

using TileLayers = std::vector<Tile *>;
using TileMapColumns = std::vector<TileLayers>;
using TileMapRows = std::vector<TileMapColumns>;
using TileMapVector = std::vector<TileMapRows>;
class LevelDesign : public std::vector<std::vector<int>> {
  public:
	// Helper function for reading a level definition from a CSV file into a vector
	bool loadFromFile(const std::string& inputFile) {
        std::ifstream in;
        in.open(inputFile);

		if(!in.is_open()) { return false; }
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

struct Stats {
	int str = 0;  // Strength
	int dex = 0;  // Dexterity
	int hp = 0;   // Health Points - Life
	int mana = 0; // Magic Energy
	Stats(const int s, const int d, const int h, const int m) : str(s), dex(d), hp(h), mana(m) {}
};