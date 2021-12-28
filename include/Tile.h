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

class Tile {
  private:
	sf::RectangleShape shape;

  public:
	bool is_solid;
	bool is_occupied;
	int doorNum;

	Tile(tson::TileObject* tileObject, MapBackground* textureSheet);
	virtual ~Tile();

	void update();
	void render(sf::RenderWindow& window);
};