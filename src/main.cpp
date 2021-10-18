#include "Game.h"
#undef main


int main()
{
    // Init game engine
    Game game;

    // Game loop
    while(game.isRunning())
    {
        // Update
        game.update();
        // Render
        game.render();
    }

    // End of application
    return 0;
}