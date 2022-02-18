#include <iterator>

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "states/MainMenuState.h"

Button::Button(const sf::Vector2f& _position, const sf::Vector2f& _size, sf::Font* _font, const std::string& _text,
    sf::Color _activeColor, sf::Color _inactiveColor) {
	buttonState = ButtonStates::BTN_IDLE;

	shape.setPosition(_position);
	shape.setSize(_size);

	font = _font;
	text.setFont(*font);
	text.setString(_text);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(12);
	shape.setOutlineThickness(1.f);
	auto Xs = shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f;
	auto Ys = shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f;

	text.setPosition(Xs, Ys);

	idleColor = _inactiveColor;
	activeColor = _activeColor;

	shape.setFillColor(idleColor);
}

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Text& newText) {
	buttonState = ButtonStates::BTN_IDLE;

	shape.setPosition(position);
	shape.setSize(size);
	text = newText;
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(20);
	text.setPosition(position.x + 5.f, position.y + 5.f);
	shape.setFillColor(sf::Color::Black);
}

Button::~Button() = default;

// Accessors
bool Button::isPressed() const {
	return (buttonState == ButtonStates::BTN_ACTIVE);
}

std::string Button::getText() const {
	return text.getString();
}

// Modifiers
void Button::setText(const std::string& _text) {
	text.setString(_text);
}

// Function
void Button::update(const Position mousePos) {
	// update the boolean for hover and pressed

	// idle
	buttonState = ButtonStates::BTN_IDLE;

	// Hover
	if(shape.getGlobalBounds().contains(mousePos)) {
		buttonState = ButtonStates::BTN_HOVER;
		// Pressed
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = ButtonStates::BTN_ACTIVE;
		}
	}

	switch(buttonState) {
	case ButtonStates::BTN_IDLE:
		shape.setFillColor(idleColor);
		shape.setOutlineColor(outlineIdleColor);
		break;
	case ButtonStates::BTN_HOVER:
		shape.setFillColor(hoverColor);
		shape.setOutlineColor(outlineHoverColor);
		break;
	case ButtonStates::BTN_ACTIVE:
		shape.setFillColor(sf::Color::Red);
		shape.setOutlineColor(outlineActiveColor);
		break;
	}
}

void Button::render(sf::RenderWindow* window) {
	window->draw(shape);
	window->draw(text);
}

void Button::setActive() {
	shape.setFillColor(activeColor);
	buttonState = ButtonStates::BTN_ACTIVE;
}
void Button::setInactive() {
	shape.setFillColor(idleColor);
	buttonState = ButtonStates::BTN_IDLE;
}

void Button::setColor(sf::Color color) {
	shape.setFillColor(color);
}