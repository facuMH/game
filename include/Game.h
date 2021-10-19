#ifndef RPG_GAME_H
#define RPG_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

struct Position{
    int x=0;
    int y=0;
    int x_offset=0;
    int y_offset=0;
    Position() : x(0), y(0), x_offset(0), y_offset(0){}
    Position(int x, int y, int x_offset, int y_offset) : x(x), y(y), x_offset(x_offset), y_offset(y_offset) {}
};

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
    sf::Sprite character_sprite;
    Position character_position;
    sf::Texture character_texture;
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
