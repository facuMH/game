#pragma once

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button {
  private:
	short unsigned buttonState;
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

  public:
	Button(
	    float x, float y, float width, float height, sf::Font* font, const std::string& text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

	~Button();

	// Accessors
	bool isPressed() const;

	// Functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void setActive();
	void setInactive();
};