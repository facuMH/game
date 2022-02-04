#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

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
	Button(float x, float y, float width, float height, sf::Font* _font, const std::string& _text, sf::Color _idleColor,
	    sf::Color _hoverColor, sf::Color _activeColor, sf::Color _outlineIdleColor = sf::Color::Transparent,
	    sf::Color _outlineHoverColor = sf::Color::Transparent, sf::Color _outlineActiveColor = sf::Color::Transparent);

	Button(float x, float y, float width, float height, const sf::Text& newText);

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
