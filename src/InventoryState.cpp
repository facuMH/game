
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "AssetsPaths.h"
#include "InventoryState.h"

#include "definitions.h"

InventoryState::InventoryState(sf::RenderWindow* window, AssetsManager& am, KeyList* _supportedKeys, Player* _player)
    : State(window) {
	view = window->getDefaultView();

	initFonts(am);
	initText(window);
	initButtons(window);
	supportedKeys = _supportedKeys;
}

void InventoryState::initBackground(sf::RenderWindow* window, AssetsManager& am) {
	// initialize shape (like the dialogue box) with enought space for the items
	// if no items then display one item called "no items here"
}

void InventoryState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

void InventoryState::initText(sf::RenderWindow* window) {
	text.setFont(font);
	text.setString(sf::String("Inventory"));
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	sf::Vector2u currentSize = window->getSize();
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(currentSize.x / 2.0f, currentSize.y / 4.0f);
}

void InventoryState::initButtons(sf::RenderWindow* window) {
	// equip and resume buttons
	// button size
	unsigned int bWidth = 150;
	unsigned int bHeight = 40;
	activeButton = 0;
	auto offsetX = 2 * bWidth;
	auto offsetY = 2 * bHeight;

	auto center = getWindowCenter(*window);
	center.x -= offsetX;
	center.y -= offsetY;
	auto bPos = center.x;

	buttons.push_back(Button(bPos, center.y, bWidth, bHeight, &font, "RESUME (R)", GREY, LIGHTGREY, sf::Color::Black));
	bPos = bPos + 3 * bWidth;
	buttons.push_back(Button(bPos, center.y, bWidth, bHeight, &font, "EQUIP (E)", GREY, LIGHTGREY, sf::Color::Black));
	buttons[activeButton].setInactive();
}

void InventoryState::updateButtons() {}

void InventoryState::renderButtons(sf::RenderWindow* window) {
	for(auto& it : buttons) {
		it.render(window);
	}
}

void InventoryState::updateMousePositions() {}

// Functions
void InventoryState::endState() {
	std::cout << "Closing Inventory!\n";
}

void InventoryState::updateInput(const float& dt) {}

void InventoryState::update(const float& dt) {
	updateButtons();
}

void InventoryState::render(sf::RenderWindow* window) {
	window->setView(view);
	// window->draw(background);
	window->draw(container);
	window->draw(text);
	renderButtons(window);
}

StateAction InventoryState::handleKeys(sf::Keyboard::Key key) {
	// up and down to to move through the items
	// E for equip selected item
	// R for resume
	return StateAction::NONE;
}

void InventoryState::updateKeybinds(const float& dt) {}

void InventoryState::quitStateActions() {
	std::cout << "Closing Inventory!\n";
}

bool InventoryState::shouldQuit() {
	return isQuit();
}

StateAction InventoryState::shouldAct() {
	// if active button is E then equip and exit state, if active button is resume just exit state
	return StateAction::NONE;
}

void InventoryState::stopMusic() {}
void InventoryState::resumeMusic() {}