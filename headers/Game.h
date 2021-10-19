#ifndef RPG_GAME_H
#define RPG_GAME_H

#include "State.h"

/*
 * Wrapper class acting as game engine.
 */
class Game
{
private:
    void initVariables();
    void initWindow();

    sf::RenderWindow *window; // dynamically allocated so that it can be deleted
    sf::VideoMode videoMode;
    sf::Event event;

    // Time variables
    sf::Clock dtClock;
    float dt; // time delta
public:
    // Constructor
    Game();

    // Destructor
    virtual ~Game();

    // Functions
    // Everything defining behind-the-scenes logic
    void update();

    // Update time variable dt (new time is the time it takes to update and render 1 frame)
    void updateDT();

    // Visual representation of the game
    void render();

    // register any events
    void pollEvents();

    // Accessors
    bool isRunning() const;
};


#endif //RPG_GAME_H
