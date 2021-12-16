#pragma once

#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <SFML/Graphics.hpp>


enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

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
	Button(float x, float y, float width, float height, sf::Font* _font, const std::string& _text, sf::Color _idleColor,
	    sf::Color _hoverColor, sf::Color _activeColor, sf::Color _outlineIdleColor = sf::Color::Transparent,
	    sf::Color _outlineHoverColor = sf::Color::Transparent, sf::Color _outlineActiveColor = sf::Color::Transparent,
	    short unsigned _id = 0);


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
       Button* activeElement;
       std::vector<Button*> list;
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

