#include "Gui.h"
#include "MainMenuState.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <cstddef>
#include <iterator>

gui::Button::Button(float x, float y, float width, float height, sf::Font* font, const std::string& text,
    sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Color outline_idle_color,
    sf::Color outline_hover_color, sf::Color outline_active_color, short unsigned id) {
	this->buttonState = BTN_IDLE;

	this->id = id;
	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);
	this->text.setPosition(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f)
	                           - this->text.getGlobalBounds().width / 2.f,
	    this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f)
	        - this->text.getGlobalBounds().height / 2.f);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;

	this->shape.setFillColor(this->idleColor);
}

// gui::Button::Button() {}

gui::Button::~Button() = default;

// Accessors
bool gui::Button::isPressed() const {
	if(buttonState == BTN_ACTIVE) return true;
	return false;
}

const std::string gui::Button::getText() const {
	return this->text.getString();
}

// Modifiers
void gui::Button::setText(const std::string text) {
	this->text.setString(text);
}

void gui::Button::setId(const unsigned short id) {
	this->id = id;
}

const short unsigned& gui::Button::getId() const {
	return id;
}

// Function
void gui::Button::update(const sf::Vector2f mousePos) {
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

void gui::Button::render(sf::RenderTarget* target) {
	target->draw(shape);
	target->draw(text);
}

void gui::Button::setActive() {
	shape.setFillColor(hoverColor);
	buttonState = BTN_ACTIVE;
}
void gui::Button::setInactive() {
	shape.setFillColor(idleColor);
	buttonState = BTN_IDLE;
}

////////////////		 DropDownList		/////////////////////

// Accessor
const bool gui::DropDownList::getkeyTime() {
	if(this->keyTime >= this->keyTimeMax) {
		return true;
	}
	return false;
}

// Functions
void gui::DropDownList::updateKeyTime(const float& dt) {
	if(this->keyTime < this->keyTimeMax) this->keyTime += 10.f * dt;
}

const unsigned short& gui::DropDownList::getActiveElementId() const {
	return this->activeElement->getId();
}

void gui::DropDownList::update(sf::Vector2f mousePos, const float& dt) {
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
void gui::DropDownList::render(sf::RenderTarget* target) {
	this->activeElement->render(target);
	if(this->showList) {
		for(auto& i : this->list) {
			i->render(target);
		}
	}
}

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[],
    unsigned nrOfElements, unsigned default_index)
    : font(font), showList(false), keyTimeMax(10.f), keyTime(keyTimeMax) {
	this->activeElement = new gui::Button(x, y, width, height, &font, list[default_index], GREY, LIGHTGREY, BLACK,
	    sf::Color::White, sf::Color::Red, sf::Color::Blue);

	for(size_t i = 0; i < nrOfElements; i++) {
		this->list.push_back(new gui::Button(x, y + (i + 1) * height, width, height, &font, list[i], GREY, LIGHTGREY,
		    BLACK, sf::Color::White, sf::Color::Blue, sf::Color::Black, i));
	}
}

gui::DropDownList::~DropDownList() {
	delete this->activeElement;
	// for(auto *&i : this->list)
	// 	delete i;

	for(size_t i = 0; i < this->list.size(); i++) {
		delete this->list[i];
	}
}