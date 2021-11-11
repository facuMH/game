#pragma once

#include "State.h"
#include "TileMap.h"

class GameState : public State {
private:
    TileMap map;
public:
  // Constructor
  explicit GameState(sf::RenderWindow *window);
  // Destructor
  ~GameState() override;

  // Functions
  void update(const float &dt) override;
  void render(sf::RenderTarget *target) override;
  void updateKeybinds(const float &dt) override;
  void checkIfQuitting() override;
  void quitStateActions() override;
};


