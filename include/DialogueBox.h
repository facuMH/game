#pragma once

#include "definitions.h"

class DialogueBox {
  private:
	short unsigned id;
	Position position;
	sf::Font* font;
	sf::Text text;
	sf::RectangleShape shape;

  public:
	DialogueBox() = default;
	DialogueBox(Position _position, sf::Font* _font, const std::string& _text);

	void update(std::string& _text);
	void render(sf::RenderWindow* window);
};

