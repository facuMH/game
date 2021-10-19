#ifndef RPG_STATE_H
#define RPG_STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <fstream>
#include <sstream>
class State
{
private:
    std::vector<sf::Texture> textures;

public:
    // Constructor
    State();
    // Destructor
    virtual ~State();

    // virtual ==> these MUST be defined in child class
    virtual void update() = 0;
    virtual void render() = 0;
};


#endif //RPG_STATE_H
