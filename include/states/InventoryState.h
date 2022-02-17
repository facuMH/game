#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Player.h"
#include "State.h"
#include "managers/AssetsManager.h"
#include "managers/ItemManager.h"

#include "definitions.h"

class InventoryState : public State {
  private:
	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Font font;
	sf::Text title;
	sf::RectangleShape titleBackground;
	const sf::Color activeItemColor = sf::Color::Red;
	const sf::Color inactiveItemColor = sf::Color::Black;

	KeyList* supportedKeys;

	int activeButton;
	Buttons buttons;

	Player* player = nullptr;
	State* previous = nullptr;
	ItemManager* itemManager = nullptr;
	std::vector<sf::Text> playerItems;
	bool emptyInventory = false;

	// Functions
	void initBackground(AssetsManager& am);
	void initFonts(AssetsManager& am);
	void initText(sf::RenderWindow* window);
	void initButtons(sf::RenderWindow* window);
	void updateButtons();
	void renderButtons(sf::RenderWindow* window);
	void updateMousePositions();
	void initPlayerItems();

  public:
	InventoryState(sf::RenderWindow* window, AssetsManager& am, KeyList* _supportedKeys, ItemManager* im,
	    Player* _player, State* _previous);
	~InventoryState() override = default;

	// Functions
	void updateInput(const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderWindow* window) override;
	StateAction handleKeys(sf::Keyboard::Key key) override;
	void updateKeybinds(const float& dt) override;
	void quitStateActions() override;
	bool shouldQuit() override;
	void drawPlayer(sf::RenderWindow* window) override {}
	StateAction shouldAct() override;
};