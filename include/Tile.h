#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "../libs/tileson.hpp"
#include "definitions.h"
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

class Tile {
  private:
  protected:
	sf::RectangleShape shape;

  public:
	Tile();

	Tile(tson::TileObject* tileObject, MapBackground* textureSheet);

	virtual ~Tile();

	void update();

	void render(sf::RenderWindow& window);
};