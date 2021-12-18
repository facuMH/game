#include <cstddef>
#include <iterator>

#include "Button.h"
#include "MainMenuState.h"

Button::Button(float x, float y, float width, float height, sf::Font* _font, const std::string& _text,
    sf::Color _idleColor, sf::Color _hoverColor, sf::Color _activeColor, sf::Color _outlineIdleColor,
    sf::Color _outlineHoverColor, sf::Color _outlineActiveColor, short unsigned _id) {
	buttonState = BTN_IDLE;

	id = _id;
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

Button::~Button() = default;

// Accessors
bool Button::isPressed() const {
	return (buttonState == BTN_ACTIVE);
}

const std::string Button::getText() const {
	return text.getString();
}

// Modifiers
void Button::setText(const std::string _text) {
	text.setString(_text);
}

void Button::setId(const unsigned short _id) {
	id = _id;
}

const short unsigned& Button::getId() const {
	return id;
}

// Function
void Button::update(const Position mousePos) {
	// update the boolean for hover and pressed

	// idle
	buttonState = BTN_IDLE;

	// Hover
	if(shape.getGlobalBounds().contains(mousePos)) {
		buttonState = BTN_HOVER;

		// Pressed
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = BTN_ACTIVE;
		}
	}

	switch(buttonState) {
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		shape.setOutlineColor(outlineIdleColor);
		break;
	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		shape.setOutlineColor(outlineHoverColor);
		break;
	case BTN_ACTIVE:
		shape.setFillColor(sf::Color::Red);
		shape.setOutlineColor(outlineActiveColor);
		break;
	default: break;
	}
}

void Button::render(sf::RenderWindow* window) {
	window->draw(shape);
	window->draw(text);
}

void Button::setActive() {
	shape.setFillColor(hoverColor);
	buttonState = BTN_ACTIVE;
}
void Button::setInactive() {
	shape.setFillColor(idleColor);
	buttonState = BTN_IDLE;
}
