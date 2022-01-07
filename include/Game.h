#pragma once

#include <unordered_map>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "AssetsManager.h"
#include "GameState.h"
#include "HouseManager.h"
#include "InteractionManager.h"
#include "MainMenuState.h"
#include "definitions.h"

/*
 * Wrapper class acting as game engine.
 */
class Game {
  private:
	void initVariables();
	void closeWindow();
	void initWindow();
	void initStates();
	void initKeys();

	// window is a pointer, since the new-operator returns a pointer to
	// the beginning of the new block of memory allocated
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event{};
	sf::Clock dtClock;

	KeyList keyBindings;
	std::unordered_map<std::string, KeyAction> keyActionString;
	std::vector<std::pair<Position, DoorNumber>> housePositions;
	AssetsManager assetsManager;
	float dt{}; // time delta
	Position_i mousePos;
	sf::Text mousePosText;

	Player player;
	InteractionManager interactionManager;
	HouseManager houseManager;

	// Stack of states - the top entry is the active state, i.e. [main menu,
	// map-layer, fight-layer]: If the fight layer is left, the next active state
	// is the map-layer. If the map-layer is left, we're at the main menu. Must be
	// a pointer, since State is an abstract class and cannot be instantiated.
	// Only instances of its child classes could be put on the stack directly.
	std::stack<State*> states;


	void makeNewCombat();
	void makeNewCombat(const Enemy* enemy);
	void makeMainGameState();
	void makeNewHouseState(Position playerPosition);
	Villager createVillager(
	    const std::string& textureName, Name name, Position position, MovementType movementDirection, float stepsize);

  public:
	// Constructor
	Game();

	// Destructor
	virtual ~Game();

	// Functions
	// Everything defining behind-the-scenes logic
	void update();

	// Update time variable dt (new time is the time it takes to update and render
	// 1 frame)
	void updateDT();

	// Visual representation of the game
	void render();

	// Register any events
	void pollEvents();

	// End the application
	static void endApplication();

	// Accessors
	bool isRunning() const;

	void turnOffMusic();
};