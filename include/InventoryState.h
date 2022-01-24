#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "AssetsManager.h"
#include "Player.h"
#include "State.h"

class InventoryState : public State {
  private:
	sf::View view;
	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Font font;
	sf::Text text;

	KeyList* supportedKeys;

	int activeButton;
	Buttons buttons;

	Player* player = nullptr;

	// Functions
	void initBackground(sf::RenderWindow* window, AssetsManager& am);
	void initFonts(AssetsManager& am);
	void initText(sf::RenderWindow* window);
	void initButtons(sf::RenderWindow* window);
	void updateButtons();
	void renderButtons(sf::RenderWindow* window);
	void updateMousePositions();

  public:
	InventoryState(sf::RenderWindow* window, AssetsManager& am, KeyList* _supportedKeys, Player* _player);
	~InventoryState() override = default;

	// Functions
	void endState();
	void updateInput(const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderWindow* window) override;
	StateAction handleKeys(sf::Keyboard::Key key) override;
	void updateKeybinds(const float& dt) override;
	void quitStateActions() override;
	bool shouldQuit() override;

	Position getCurrentPlayerPosition() override { return {0, 0}; };
	void drawPlayer(sf::RenderWindow* window) override {}
	sf::View getView() override { return view; };

	StateAction shouldAct() override;
	void stopMusic() override;
	void resumeMusic() override;
};