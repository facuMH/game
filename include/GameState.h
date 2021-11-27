#pragma once

#include "AssetsManager.h"
#include "State.h"
#include "TileMap.h"

class GameState : public State {
private:
    TileMap map;
public:
  // Constructor
  GameState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns);
  // Destructor
  ~GameState() override;

  // Functions
  void update(const float &dt) override;
  void render(sf::RenderTarget *target) override;
  void updateKeybinds(const float &dt) override;
  void checkIfQuitting() override;
  void quitStateActions() override;
};


