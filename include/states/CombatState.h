#pragma once

#include "AssetsManager.h"
#include "Enemy.h"
#include "ItemManager.h"
#include "Player.h"
#include "State.h"
#include "TileMap.h"
#include "definitions.h"
#include "entity_attributes/Combatant.h"

constexpr int COMBAT_MENU_X = 320;
constexpr int COMBAT_MENU_Y = 300;

constexpr int bWidth = 150;
constexpr int bHeight = 40;

constexpr float ITEMS_MENU_X = COMBAT_MENU_X;
// 4 = 2 free spaces + 2 usable items at most.
constexpr float ITEMS_MENU_Y = COMBAT_MENU_Y - bHeight * 4;

class CombatState : public State {
  private:
	sf::View view;

	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	sf::Music music;
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
	Buttons playerItems;
	bool emptyInventory = false;

	void addActionMenu();
	void addCombatString(const Player& player, AssetsManager& am);
	void initPlayerItems(const ItemManager* itemManager);

  public:
	// Constructor
	CombatState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
	    JSONFilePath& path, const Player& p, const Enemy& e, KeyList* gameSupportedKeys, const ItemManager* im);

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
	StateAction programAction() override;
	void drawPlayer(sf::RenderWindow* window) override;
	int experienceFromEnemy() const { return enemy.getExperience(); }
	sf::View getView() override { return view; };
	void stopMusic() override;
	void resumeMusic() override;

	void LevelUpMessage();
};