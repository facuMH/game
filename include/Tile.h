#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "tileson.hpp"
#include "definitions.h"
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

/// Class that defines a tile in a TileMap
class Tile {
  private:
	sf::RectangleShape shape;

  public:
	bool is_solid;
	bool is_occupied = false;
	DoorNumber doorNum;

	Tile(tson::TileObject* tileObject, MapBackground* textureSheet);
	virtual ~Tile();
	Position get_position();
	void update();
	void render(sf::RenderWindow& window);
};