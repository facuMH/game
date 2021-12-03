#pragma once

#include "AssetsManager.h"
#include "Characters.h"
#include "State.h"
#include "TileMap.h"
#include "definitions.h"

class CombatState : public State {
  private:
	Party party;
	Enemies enemies;
	TileMap map;
	CombatText lifeCounters;
	void addCombatString(const Character& c, AssetsManager& am);

  public:
	// Constructor
	CombatState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns, const Party& p, const Enemies& e);
	// Destructor
	~CombatState() override;

	// Functions
	void update(const float& dt) override;
	void render(sf::RenderTarget* target) override;
	void updateKeybinds(const float& dt) override;
	bool shouldQuit() override;
	void quitStateActions() override;
	StateAction handleKeys(sf::Keyboard::Key key, sf::View* view) override;
	void drawPlayer(sf::RenderWindow* window) override;
	StateAction shouldAct() override;
};