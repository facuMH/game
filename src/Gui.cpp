#include "Gui.h"
#include "MainMenuState.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <cstddef>
#include <iterator>

Button::Button(float x, float y, float width, float height, sf::Font* _font, const std::string& _text,
    sf::Color _idleColor, sf::Color _hoverColor, sf::Color _activeColor, sf::Color _outlineIdleColor,
    sf::Color _outlineHoverColor, sf::Color _outlineActiveColor, short unsigned _id) {
	buttonState = BTN_IDLE;

	id = _id;
	shape.setPosition(Position(x, y));
	shape.setSize(sf::Vector2f(width, height));

	font = _font;
	text.setFont(*font);
	text.setString(_text);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(12);
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(_outlineIdleColor);
	text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f,
			shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f
		     );

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
	if(buttonState == BTN_ACTIVE) return true;
	return false;
}

const std::string Button::getText() const {
	return this->text.getString();
}

// Modifiers
void Button::setText(const std::string text) {
	this->text.setString(text);
}

void Button::setId(const unsigned short id) {
	this->id = id;
}

const short unsigned& Button::getId() const {
	return id;
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
	case BTN_IDLE:
		shape.setFillColor(this->idleColor);
		shape.setOutlineColor(outlineIdleColor);
		break;
	case BTN_HOVER:
		shape.setFillColor(this->hoverColor);
		shape.setOutlineColor(outlineHoverColor);
		break;
	case BTN_ACTIVE:
		shape.setFillColor(sf::Color::Red);
		shape.setOutlineColor(outlineActiveColor);
		break;
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

////////////////		 DropDownList		/////////////////////

// Accessor
const bool DropDownList::getkeyTime() {

	return this->keyTime >= this->keyTimeMax;
}

// Functions
void DropDownList::updateKeyTime(const float& dt) {
	if(this->keyTime < this->keyTimeMax) this->keyTime += 10.f * dt;
}

const unsigned short& DropDownList::getActiveElementId() const {
	return this->activeElement->getId();
}

void DropDownList::update(sf::Vector2f mousePos, const float& dt) {
	this->updateKeyTime(dt);
	this->activeElement->update(mousePos);

	// Show and hide the list
	if(this->activeElement->isPressed() && this->getkeyTime()) {
		if(this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if(this->showList) {
		for(auto& i : this->list) {
			i->update(mousePos);

			if(i->isPressed() && this->getkeyTime()) {
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}
void DropDownList::render(sf::RenderTarget* target) {
	this->activeElement->render(target);
	if(this->showList) {
		for(auto& i : this->list) {
			i->render(target);
		}
	}
}

DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[],
    unsigned nrOfElements, unsigned default_index)
    : font(font), showList(false), keyTimeMax(10.f), keyTime(keyTimeMax) {
	this->activeElement = new Button(x, y, width, height, &font, list[default_index], GREY, LIGHTGREY, BLACK,
	    sf::Color::White, sf::Color::Red, sf::Color::Blue);

	for(size_t i = 0; i < nrOfElements; i++) {
		this->list.push_back(new Button(x, y + (i + 1) * height, width, height, &font, list[i], GREY, LIGHTGREY,
		    BLACK, sf::Color::White, sf::Color::Blue, sf::Color::Black, i));
	}
}

DropDownList::~DropDownList() {
	delete this->activeElement;

	for(size_t i = 0; i < this->list.size(); i++) {
		delete this->list[i];
	}
}
