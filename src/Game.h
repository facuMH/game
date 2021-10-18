#ifndef RPG_GAME_H
#define RPG_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

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
public:
    // Constructor
    Game();

    // Destructor
    virtual ~Game();

    // Functions
    // Everything defining behind-the-scenes logic
    void update();

    // Visual representation of the game
    void render();

    void pollEvents();

    // Accessors
    bool isRunning() const;
};


#endif //RPG_GAME_H
