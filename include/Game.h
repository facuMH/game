#ifndef RPG_GAME_H
#define RPG_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <unordered_map>

#include "Characters.h"
#include "GameState.h"
#include "MapTiles.h"

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

    Character player;

    // this should be moved a "LoadAssets" function where textures are loaded.
    sf::Texture character_texture_idle;
    sf::Texture character_texture_run;
    std::vector<sf::Texture> player_textures;

    sf::Clock clock;

    // Time variables
    sf::Clock dtClock;
    float dt; // time delta

    // Stack of states - the top entry is the active state, i.e. [main menu, map-layer, fight-layer]:
    // If the fight layer is left, the next active state is the map-layer.
    // If the map-layer is left, we're at the main menu.
    std::stack<State*> states;

    //std::unordered_map<Position, MapTile> MapTiles;

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
