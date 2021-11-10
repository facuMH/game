#pragma once

#include "State.h"
#include "Characters.h"
#include "definitions.h"

class GameState : public State {
public:
  // Constructor
  explicit GameState(sf::RenderWindow *window);
  // Destructor
  ~GameState() override;

  // Functions
  void update(const float &dt) override;
  void render(sf::RenderTarget *target) override;
  void updateKeybinds(const float &dt) override;
  bool shouldQuit() override;
  void quitStateActions() override;
};

class CombatState : public State {
private:
  Party party;
  Enemies enemies;

public:
  // Constructor
  explicit CombatState(sf::RenderWindow *window, Party p, Enemies e);
  // Destructor
  ~CombatState() override;

  // Functions
  void update(const float &dt) override;
  void render(sf::RenderTarget *target) override;
  void updateKeybinds(const float &dt) override;
  bool shouldQuit() override;
  void quitStateActions() override;
};