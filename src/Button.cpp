#include "Button.h"

Button::Button(
    float x, float y, float width, float height, sf::Font* font, const std::string& text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) {
	this->buttonState = BTN_IDLE;

	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);
	this->text.setPosition(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
	    this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
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
	case BTN_IDLE: shape.setFillColor(this->idleColor); break;
	case BTN_HOVER: shape.setFillColor(this->hoverColor); break;
	case BTN_ACTIVE: shape.setFillColor(sf::Color::Red); break;
	default: break;
	}
}

void Button::render(sf::RenderTarget* target) {
	target->draw(shape);
	target->draw(text);
}

void Button::setActive() {
	shape.setFillColor(hoverColor);
	buttonState = BTN_ACTIVE;
}
void Button::setInactive() {
	shape.setFillColor(idleColor);
	buttonState = BTN_IDLE;
}