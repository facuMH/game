#pragma once

#include "AssetsManager.h"
#include "Characters.h"
#include "State.h"
#include "TileMap.h"

class GameState : public State {
  private:
	TileMap map;
	Character player;
	AssetsManager* am;
	sf::Clock clock;

  public:
	// Constructor
	GameState(sf::RenderWindow* window, AssetsManager& am);
	// Destructor
	~GameState() override;

	// Functions
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
	void updateKeybinds(const float& dt) override;
	void checkIfQuitting() override;
	void quitStateActions() override;
	void handleKeys(sf::Keyboard::Key key) override;
	void player_idle();
	//void initKeybinds();
};
