#pragma once

#include "AssetsManager.h"
#include "Characters.h"
#include "State.h"
#include "TileMap.h"
#include "definitions.h"

class GameState : public State {
  private:
	TileMap map;

  public:
	// Constructor
	explicit GameState(sf::RenderWindow* window, AssetsManager& am, const std::string& level);
	// Destructor
	~GameState() override;

	// Functions
	void update(const float& dt) override;
	void render(sf::RenderTarget* target) override;
	void updateKeybinds(const float& dt) override;
	bool shouldQuit() override;
	void quitStateActions() override;
};

class CombatState : public State {
  private:
	Party party;
	Enemies enemies;
	TileMap map;

  public:
	// Constructor
	explicit CombatState(sf::RenderWindow* window, AssetsManager& am, Party p, Enemies e, const std::string& level);
	// Destructor
	~CombatState() override;

	// Functions
	void update(const float& dt) override;
	void render(sf::RenderTarget* target) override;
	void updateKeybinds(const float& dt) override;
	bool shouldQuit() override;
	void quitStateActions() override;
};