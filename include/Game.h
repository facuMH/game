#ifndef RPG_GAME_H
#define RPG_GAME_H


#include "GameState.h"
#include "Entity.h"


/*
 * Wrapper class acting as game engine.
 */
class Game
{
private:
    void initVariables();
    void initWindow();
    void initStates();

    sf::RenderWindow *window; // dynamically allocated so that it can be deleted
    sf::VideoMode videoMode;
    sf::Event event;

    sf::Sprite character_sprite;
    sf::IntRect character_position;
    sf::Texture character_texture_idle;
    sf::Texture character_texture_run;
    sf::Clock clock;

    // Time variables
    sf::Clock dtClock;
    float dt; // time delta

    // Stack of states - the top entry is the active state, i.e. [main menu, map-layer, fight-layer]:
    // If the fight layer is left, the next active state is the map-layer.
    // If the map-layer is left, we're at the main menu.
    std::stack<State*> states;

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
