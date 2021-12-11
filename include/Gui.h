#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui {

class Button {
  private:
	short unsigned buttonState;
	short unsigned id;
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	sf::Color outlineIdleColor;
	sf::Color outlineHoverColor;
	sf::Color outlineActiveColor;

  public:
	Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, sf::Color idleColor,
	    sf::Color hoverColor, sf::Color activeColor, sf::Color outline_idle_color = sf::Color::Transparent,
	    sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
	    short unsigned id = 0);


	Button();

	~Button();

	// Accessors
	bool isPressed() const;
	const std::string getText() const;
	const short unsigned& getId() const;

	// Modifiers
	void setText(const std::string text);
	void setId(const short unsigned id);

	// Functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void setActive();
	void setInactive();
};

class DropDownList {
  private:
	float keyTime;
	float keyTimeMax;
	sf::Font& font;
	gui::Button* activeElement;
	std::vector<gui::Button*> list;
	bool showList;

  public:
	DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements,
	    unsigned default_index = 0);
	~DropDownList();

	// Accessors
	const unsigned short& getActiveElementId() const;

	// Functions
	const bool getkeyTime();
	void updateKeyTime(const float& dt);
	void update(sf::Vector2f mousePos, const float& dt);
	void render(sf::RenderTarget* target);
	void setActive();
	void setInactive();
};

} // namespace gui