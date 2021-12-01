#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

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

	Tile(float x, float y, float gridSize, const sf::Texture* texture, sf::IntRect rect);

	virtual ~Tile();

	void update();

	void render(sf::RenderTarget& target);
};