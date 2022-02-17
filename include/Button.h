#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


enum class ButtonStates { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button {
  private:
	ButtonStates buttonState;
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
	Button(const sf::Vector2f& _position, const sf::Vector2f& size, sf::Font* _font, const std::string& _text,
	    sf::Color ActiveColor, sf::Color InactiveColor);

	Button(const sf::Vector2f& _position, const sf::Vector2f& size, const sf::Text& newText);

	~Button();

	// Accessors
	bool isPressed() const;
	std::string getText() const;

	// Modifiers
	void setText(const std::string& text);

	// Functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderWindow* window);
	void setActive();
	void setInactive();
	void setColor(sf::Color color);
};
