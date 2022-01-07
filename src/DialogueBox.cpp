#include "DialogueBox.h"

DialogueBox::DialogueBox(Position _position, sf::Font* _font, const std::string& _text) {
	shape.setPosition(_position);
	shape.setSize({25.0f, 35.0f});
	font = _font;
	text.setFont(*font);
	text.setString(_text);
	shape.setFillColor(sf::Color::White);
}

void DialogueBox::update(std::string& _text) {
	text.setString(_text);
}

void DialogueBox::render(sf::RenderWindow* window) {
	window->draw(shape);
	window->draw(text);
}

