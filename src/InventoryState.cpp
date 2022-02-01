#include <format>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "AssetsPaths.h"
#include "InventoryState.h"

constexpr int END_STATE_BUTTONS = 2;

InventoryState::InventoryState(sf::RenderWindow* window, AssetsManager& am, KeyList* _supportedKeys, ItemManager* im,
    Player* _player, State* _previous)
    : State(window), player(_player), previous(_previous), supportedKeys(_supportedKeys), itemManager(im) {
	view = window->getDefaultView();
	initFonts(am);
	initText(window);
	initButtons(window);
	initPlayerItems();
	initBackground(window, am);
	supportedKeys = _supportedKeys;

	auto soundBuffer = am.getSoundBuffer(MENU_BLIP.c);
	blipSound.setBuffer(soundBuffer);
}

void InventoryState::initPlayerItems() {
	sf::Text itemText;
	itemText.setFont(font);
	itemText.setCharacterSize(15);
	itemText.setStyle(sf::Text::Bold);
	itemText.setFillColor(sf::Color::Black);
	itemText.move({10, 5 + INVENTORY_ITEM_HEIGHT * playerItems.size()});
	if(itemManager->playerInventory.empty()) {
		itemText.setString("No items here yet.\n Go look around");
		playerItems.push_back(itemText);
	} else {
		for(const auto item : itemManager->playerInventory) {
			itemText.setString(item.c_str());
			itemText.move({10, INVENTORY_ITEM_HEIGHT * playerItems.size()});
			playerItems.push_back(itemText);
		}
	}
	playerItems.front().setOutlineColor(activeItemColor);
}

void InventoryState::initBackground(sf::RenderWindow* window, AssetsManager& am) {
	background.setTexture(am.getTexture(DIALOGUE_BOX.c));
	background.setSize({INVENTORY_ITEM_WIDTH+40, INVENTORY_ITEM_HEIGHT * static_cast<float>(playerItems.size()) + 40.f});
	background.move({0, -10});
}

void InventoryState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

void InventoryState::initText(sf::RenderWindow* window) {
	title.setFont(font);
	title.setString(sf::String("Inventory"));
	title.setCharacterSize(20);
	title.setStyle(sf::Text::Bold);
	sf::Vector2u currentSize = window->getSize();
	sf::FloatRect textRect = title.getLocalBounds();
	title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	title.setPosition(currentSize.x / 2.0f, currentSize.y / 4.0f);
}

void InventoryState::initButtons(sf::RenderWindow* window) {
	// equip and resume buttons
	// button size
	unsigned int bWidth = 150;
	unsigned int bHeight = 40;
	activeButton = 0;
	auto offsetX = bWidth;
	auto offsetY = 2 * bHeight;

	auto center = getWindowCenter(*window);
	auto bPos = center.x - offsetX;
	center.y = 0;

	buttons.push_back(Button(
	    bPos, center.y, bWidth, bHeight, &font, "RESUME (R)", sf::Color::Black, sf::Color::Black, sf::Color::Black));
	bPos = bPos + offsetX;
	buttons.push_back(Button(bPos, center.y, bWidth, bHeight, &font, "EQUIP/CONSUME (E)", sf::Color::Black,
	    sf::Color::Black, sf::Color::Black));
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
	previous->render(window);
	window->setView(view);
	window->draw(background);
	window->draw(container);
	window->draw(title);
	for(const auto item : playerItems) {
		window->draw(item);
	}
	renderButtons(window);
}

StateAction InventoryState::handleKeys(sf::Keyboard::Key key) {
	// up and down to to move through the items
	auto action = std::find_if(supportedKeys->begin(), supportedKeys->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != supportedKeys->end()) {
		switch(action->first) {
		case KeyAction::UP: // Up arrow
			playerItems[activeButton].setOutlineColor(inactiveItemColor);
			if(activeButton == 0) {
				activeButton = playerItems.size() - 1;
			} else {
				activeButton--;
			}
			playerItems[activeButton].setOutlineColor(activeItemColor);
			break;
		case KeyAction::DOWN: // Down arrow
			playerItems[activeButton].setOutlineColor(inactiveItemColor);
			if(activeButton == playerItems.size() - 1) {
				activeButton = 0;
			} else {
				activeButton++;
			}
			playerItems[activeButton].setOutlineColor(activeItemColor);
			break;
		default: break;
		}
	}
	StateAction result = StateAction::NONE;
	// E for equip selected item
	if(key == sf::Keyboard::E) {
		if(itemManager->playerInventory.size() == 0) {
			playerItems.front().setString("You cant equip anything\nbecause you dont have\nanything");
		} else {
			const auto item = itemManager->get(playerItems[activeButton].getString());
			if(item->can_equip) {
				title.setString(item->getName()+" equipped");
				player->equip(item);
			} else {
				title.setString(item->getName() + " consumed. Now you feel better.");
				player->heal(item->getStats().hp);
				playerItems.erase(std::find_if(playerItems.begin(), playerItems.end(),
				    [item](sf::Text t) { return t.getString() == item->getName(); }));
			}
		}
	}
	// R for resume
	if(key == sf::Keyboard::R) result = StateAction::CLOSE_INVENTORY;
	blipSound.play();
	return result;
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