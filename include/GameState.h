#pragma once

#include "State.h"
#include "TileMap.h"

class GameState : public State {
private:
    TileMap map;
public:
  // Constructor
   GameState(sf::RenderWindow *window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
  // Destructor
  ~GameState() override;

  // Functions
  void update(const float &dt) override;
  void render(sf::RenderTarget *target = nullptr) override;
  void updateKeybinds(const float &dt) override;
  void checkIfQuitting() override;
  void quitStateActions() override;

  void initKeybinds();
};


