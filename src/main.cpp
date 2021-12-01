#include "Game.h"

int main() {
  // Init game engine
  Game game;

  // Game loop
  while (game.isRunning()) {
    // Update time
    game.updateDT();
    // Update
    game.update();
    // Render
    game.render();
  }

  // End of application
  return 0;
}