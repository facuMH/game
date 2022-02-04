#include <cstddef>
#include <iterator>

#include "Button.h"
#include "states/MainMenuState.h"

Button::Button(float x, float y, float width, float height, sf::Font* _font, const std::string& _text,
    sf::Color _idleColor, sf::Color _hoverColor, sf::Color _activeColor, sf::Color _outlineIdleColor,
    sf::Color _outlineHoverColor, sf::Color _outlineActiveColor) {
	buttonState = ButtonStates::BTN_IDLE;

	shape.setPosition(Position(x, y));
	shape.setSize(Position(width, height));

	font = _font;
	text.setFont(*font);
	text.setString(_text);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(12);
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(_outlineIdleColor);
	auto Xs = shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f;
	auto Ys = shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f;

	text.setPosition(Xs, Ys);

	idleColor = _idleColor;
	hoverColor = _hoverColor;
	activeColor = _activeColor;

	outlineIdleColor = _outlineIdleColor;
	outlineHoverColor = _outlineHoverColor;
	outlineActiveColor = _outlineActiveColor;

	shape.setFillColor(idleColor);
}

Button::Button(float x, float y, float width, float height, const sf::Text& newText) {
	buttonState = ButtonStates::BTN_IDLE;

	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));
	text = newText;
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(20);
	text.setPosition(x + 5.f, y + 5.f);
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
	shape.setFillColor(hoverColor);
	buttonState = ButtonStates::BTN_ACTIVE;
}
void Button::setInactive() {
	shape.setFillColor(idleColor);
	buttonState = ButtonStates::BTN_IDLE;
}

void Button::setColor(sf::Color color) {
	shape.setFillColor(color);
}