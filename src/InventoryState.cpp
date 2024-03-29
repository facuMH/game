#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "AssetsPaths.h"
#include "states/InventoryState.h"

constexpr float INVENTORY_ITEM_WIDTH = 100.f;
constexpr float INVENTORY_ITEM_HEIGHT = 20.f;
constexpr float SPACE_FOR_EMPTY_INVENTORY_MESSAGE = 80.f + INVENTORY_ITEM_WIDTH;
const sf::Vector2f EMPTY_INVENTORY_SIZE = {SPACE_FOR_EMPTY_INVENTORY_MESSAGE, 90.f};
constexpr int BOX_POSITION_OFFSET = 10;
constexpr float MINIMAL_INVENTORY_HEIGHT = 60.f;
constexpr int END_STATE_BUTTONS = 2;

InventoryState::InventoryState(sf::RenderWindow* window, AssetsManager& am, KeyList* _supportedKeys, ItemManager* im,
    Player* _player, State* _previous)
    : State(window), player(_player), previous(_previous), supportedKeys(_supportedKeys), itemManager(im) {
	view = window->getDefaultView();
	initFonts(am);
	initText(window);
	initButtons(window);
	initPlayerItems();
	initBackground(am);
	initBodyParts();
	initBodyPartBackground(am, im);

	supportedKeys = _supportedKeys;
	activeButton = 0;
	playerItems[activeButton].setFillColor(activeItemColor);

	soundBuffers.emplace("blip", am.getSoundBuffer(MENU_BLIP.c));

	for(auto& sb : soundBuffers) {
		sf::Sound sound;
		sound.setBuffer(sb.second);
		sounds.emplace(sb.first, sound);
	}
}

void InventoryState::initPlayerItems() {
	sf::Text itemText;
	itemText.setFont(font);
	itemText.setCharacterSize(15);
	itemText.setStyle(sf::Text::Bold);
	itemText.setFillColor(sf::Color::Black);
	if(itemManager->playerInventory.empty()) {
		emptyInventory = true;
		itemText.setPosition({BOX_POSITION_OFFSET, BOX_POSITION_OFFSET});
		itemText.setString("No items here yet.\n Go look around");
		playerItems.push_back(itemText);
	} else {
		for(const auto& item : itemManager->playerInventory) {
			itemText.setString(item.c_str());
			itemText.setPosition(
			    {BOX_POSITION_OFFSET, BOX_POSITION_OFFSET + INVENTORY_ITEM_HEIGHT * playerItems.size()});
			playerItems.push_back(itemText);
		}
	}
	playerItems.front().setOutlineColor(activeItemColor);
}

void InventoryState::initBodyParts() {
	sf::Text itemText;
	itemText.setFont(font);
	itemText.setCharacterSize(15);
	itemText.setStyle(sf::Text::Bold);
	itemText.setFillColor(sf::Color::Black);
	if(itemManager->grandmaParts.empty()) {
		itemText.setPosition({INVENTORY_ITEM_WIDTH * 5, BOX_POSITION_OFFSET});
		itemText.setString("No grandma parts here yet.\n Go kill look around");
		bodyParts.push_back(itemText);
	} else {
		for(const auto& item : itemManager->grandmaParts) {
			itemText.setString(item.c_str());
			itemText.setPosition(
			    {INVENTORY_ITEM_WIDTH * 5, BOX_POSITION_OFFSET + INVENTORY_ITEM_HEIGHT * bodyParts.size()});
			bodyParts.push_back(itemText);
		}
	}
	bodyParts.front().setOutlineColor(inactiveItemColor);
}

void InventoryState::initBackground(AssetsManager& am) {
	background.setTexture(am.getTexture(INVENTORY.c));
	if(!emptyInventory) {
		background.setSize({INVENTORY_ITEM_WIDTH,
		    INVENTORY_ITEM_HEIGHT * static_cast<float>(playerItems.size()) + MINIMAL_INVENTORY_HEIGHT});
	} else {
		background.setSize(EMPTY_INVENTORY_SIZE);
	}
	background.move({0, -BOX_POSITION_OFFSET - 4 * static_cast<float>(playerItems.size())});
}

void InventoryState::initBodyPartBackground(AssetsManager& am, ItemManager* im) {
	bodyPartyBackground.setTexture(am.getTexture(INVENTORY.c));
	if(!im->grandmaParts.empty()) {
		bodyPartyBackground.setSize({INVENTORY_ITEM_WIDTH,
		    INVENTORY_ITEM_HEIGHT * static_cast<float>(bodyParts.size()) + MINIMAL_INVENTORY_HEIGHT});
	} else {
		bodyPartyBackground.setSize({EMPTY_INVENTORY_SIZE.x + 25, EMPTY_INVENTORY_SIZE.y});
	}
	bodyPartyBackground.move(
	    {INVENTORY_ITEM_WIDTH * 5 - 5, -BOX_POSITION_OFFSET - 4 * static_cast<float>(bodyParts.size())});
}

void InventoryState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}


void InventoryState::initText(sf::RenderWindow* window) {
	title.setFont(font);
	title.setString(sf::String("Inventory"));
	title.setCharacterSize(30);
	title.setStyle(sf::Text::Bold);
	sf::Vector2u currentSize = window->getSize();
	sf::FloatRect textRect = title.getLocalBounds();
	title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	title.setPosition(currentSize.x / 2.0f, currentSize.y / 4.0f);
	titleBackground.setFillColor(sf::Color::Black);
	Position pos = title.getPosition();
	float w = 150;
	float h = 50;
	titleBackground.setPosition({pos.x - w / 2.f, pos.y - h / 2.f});
	titleBackground.setSize({w * 2, h});
}

void InventoryState::initButtons(sf::RenderWindow* window) {
	// equip and resume buttons
	// button size
	const int bWidth = 150;
	const int bHeight = 40;
	activeButton = 0;
	auto offsetX = bWidth;

	auto center = getWindowCenter(*window);
	auto bPos = center.x - offsetX;
	center.y = 0;

	buttons.push_back(
	    Button({bPos, center.y}, {bWidth, bHeight}, &font, "RESUME (R)", sf::Color::Black, sf::Color::Black));
	bPos = bPos + offsetX;
	buttons.push_back(
	    Button({bPos, center.y}, {bWidth, bHeight}, &font, "EQUIP/CONSUME (E)", sf::Color::Black, sf::Color::Black));
	buttons[activeButton].setInactive();
}

void InventoryState::updateButtons() {}

void InventoryState::renderButtons(sf::RenderWindow* window) {
	for(auto& it : buttons) {
		it.render(window);
	}
}

void InventoryState::updateMousePositions() {}

void InventoryState::update(const float& dt) {
	updateButtons();
}

void InventoryState::render(sf::RenderWindow* window) {
	previous->render(window);
	window->setView(view);
	window->draw(background);
	window->draw(titleBackground);
	window->draw(title);
	for(const auto& item : playerItems) {
		window->draw(item);
	}
	window->draw(bodyPartyBackground);
	for(const auto& item : bodyParts) {
		window->draw(item);
	}

	renderButtons(window);
}

StateAction InventoryState::handleKeys(sf::Keyboard::Key key) {
	// up and down to move through the items
	auto action = std::find_if(supportedKeys->begin(), supportedKeys->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != supportedKeys->end()) {
		switch(action->first) {
		case KeyAction::UP: // Up arrow
			playerItems[activeButton].setFillColor(inactiveItemColor);
			if(activeButton == 0) {
				activeButton = playerItems.size() - 1;
			} else {
				activeButton--;
			}
			playerItems[activeButton].setFillColor(activeItemColor);
			break;
		case KeyAction::DOWN: // Down arrow
			playerItems[activeButton].setFillColor(inactiveItemColor);
			if(activeButton == playerItems.size() - 1) {
				activeButton = 0;
			} else {
				activeButton++;
			}
			playerItems[activeButton].setFillColor(activeItemColor);
			break;
		default: break;
		}
	}
	StateAction result = StateAction::NONE;
	// E for equip selected item
	if(key == sf::Keyboard::E) {
		if(itemManager->playerInventory.empty()) {
			playerItems.front().setString("You cant equip anything\nbecause you dont have\nanything");
		} else {
			const auto item = itemManager->get(playerItems[activeButton].getString());
			if(item->can_equip) {
				title.setString(item->getName() + " equipped");
				player->equip(item);
			} else {
				title.setString(item->getName() + " consumed. Now you feel better.");
				player->heal(item->getStats().hp);
				playerItems.erase(std::find_if(playerItems.begin(), playerItems.end(),
				    [item](sf::Text& t) { return t.getString() == item->getName(); }));
				activeButton = 0;
				playerItems[activeButton].setFillColor(activeItemColor);
			}
		}
	}
	// R for resume
	if(key == sf::Keyboard::R) result = StateAction::CLOSE_INVENTORY;
	sounds.find("blip")->second.play();
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