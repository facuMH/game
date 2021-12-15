#include "Button.h"
#include "definitions.h"

Button::Button(
    float x, float y, float width, float height, sf::Font* newFont, const std::string& newText, sf::Color newIdleColor, sf::Color newHoverColor, sf::Color newActiveColor) {
	buttonState = BTN_IDLE;

	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));

	font = newFont;
	text.setFont(*font);
	text.setString(newText);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(12);
	text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f,
	    shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f);

	idleColor = newIdleColor;
	hoverColor = newHoverColor;
	activeColor = newActiveColor;

	shape.setFillColor(idleColor);
}

Button::Button(float x, float y, float width, float height, const sf::Text newText) {
	buttonState = BTN_IDLE;

	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));
	text = newText;
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(20);
	auto Xs = shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f;
	auto Ys = shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f;
	text.setPosition(Xs, Ys);
	shape.setFillColor(sf::Color::Black);
}

Button::~Button() = default;

// Accessors
bool Button::isPressed() const {
	if(buttonState == BTN_ACTIVE) return true;
	return false;
}

// Function
void Button::update(const sf::Vector2f mousePos) {
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
	case BTN_IDLE: shape.setFillColor(idleColor); break;
	case BTN_HOVER: shape.setFillColor(hoverColor); break;
	case BTN_ACTIVE: shape.setFillColor(sf::Color::Red); break;
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