#pragma once

#include "AssetsManager.h"
#include "Enemy.h"
#include "Player.h"
#include "State.h"
#include "TileMap.h"
#include "definitions.h"
#include "entity_attributes/Combatant.h"

class CombatState : public State {
  private:
	sf::Font font;
	Player player;
	Enemy enemy;
	TileMap map;
	std::unique_ptr<Button> levelUpBox;
	bool inLevelUpBox = false;
	KeyList* keybinds;

	CombatText lifeCounters;
	Position initialText{10.f, 300.f};
	float textIntervalHeight = 50;

	std::vector<Entity*> turnList;
	int currentCharacterTurn;
	bool nextTurn;

	Animation cursor;
	int cursorOrientation;
	sf::Clock cursorClock;

	Buttons actionButtons;
	int actionButtonActive;
	bool selectingEnemy;
	bool selectingItem;
	bool isSpecialAtk;

	void addActionMenu();
	void addCombatString(const Player& player, AssetsManager& am);
  public:
	// Constructor
	CombatState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
	    JSONFilePath& path, const Player& p, const Enemy& e, KeyList* gameSupportedKeys);

	// Destructor
	~CombatState() override;

	// Functions
	void update(const float& dt) override;
	void render(sf::RenderWindow* window) override;
	void updateKeybinds(const float& dt) override;
	bool shouldQuit() override;
	void quitStateActions() override;
	StateAction handleKeys(sf::Keyboard::Key key) override;
	StateAction shouldAct() override;

	StateAction programAction();
	void drawPlayer(sf::RenderWindow* window);
	int experienceFromEnemy() const { return enemy.getExperience(); }
	void LevelUpMessage();
};