#pragma once

#include "AssetsManager.h"
#include "State.h"
#include "TileMap.h"

class GameState : public State {
  private:
	TileMap map;

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

	//void initKeybinds();
};
