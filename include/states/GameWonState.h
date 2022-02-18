#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "State.h"
#include "managers/AssetsManager.h"

/// State which shows a Game Won screen which marks the end of the game
class GameWonState : public State {
  private:
	sf::RectangleShape background;

	// Functions
	void initBackground(AssetsManager& am);

  public:
	GameWonState(sf::RenderWindow* window, AssetsManager& _assetsManager);

	// Functions
	void update(const float& dt) override;
	void render(sf::RenderWindow* window) override;
	StateAction handleKeys(sf::Keyboard::Key key) override;
	void updateKeybinds(const float& dt) override;
	void quitStateActions() override;
	bool shouldQuit() override;
	void drawPlayer(sf::RenderWindow* window) override{};
	StateAction shouldAct() override;
	StateAction programAction() override { return StateAction::NONE; };
};