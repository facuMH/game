#pragma once

#include "GameState.h"

/*
 * Wrapper class acting as game engine.
 */
class Game {
private:
  void initVariables();
  void initWindow();
  void initStates();

  // window is a pointer, since the new-operator returns a pointer to
  // the beginning of the new block of memory allocated
  sf::RenderWindow *window;
  sf::VideoMode videoMode;
  sf::Event event{};

  // Time variables
  sf::Clock dtClock;
  float dt{}; // time delta

  // Stack of states - the top entry is the active state, i.e. [main menu,
  // map-layer, fight-layer]: If the fight layer is left, the next active state
  // is the map-layer. If the map-layer is left, we're at the main menu. Must be
  // a pointer, since State is an abstract class and cannot be instantiated.
  // Only instances of its child classes could be put on the stack directly.
  std::stack<State *> states;

public:
  // Constructor
  Game();

  // Destructor
  virtual ~Game();

  // Update functions
  // Everything defining behind-the-scenes logic
  void update();
  // Update time variable dt (new time is the time it takes to update and render
  // 1 frame)
  void updateDT();

  // Render functions
  // Visual representation of the game
  void render();

  // Register any events
  void pollEvents();

  // End the application
  static void endApplication();

  // Accessors
  bool isRunning() const;
};