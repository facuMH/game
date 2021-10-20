#include <iostream>

#include "Game.h"


// Private functions
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode.height = 720;
    this->videoMode.width = 1280;

    this->window = new sf::RenderWindow(this->videoMode, "game", sf::Style::Titlebar | sf::Style::Close);

    if (!character_texture.loadFromFile("../assets/character/Idle.png")){
        std::cout << "character not found in: " <<  "assets/character/Idle.png" << "\n";
    }
    character_position= sf::IntRect(65,55,45,40);
    character_texture.setSmooth(true);
    character_sprite.setTexture(character_texture);
    character_sprite.setTextureRect(character_position);
    character_sprite.scale(sf::Vector2f(3.f, 3.f)); 
}

// Constructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

// Destructor
Game::~Game()
{
    delete this->window;
}

// Accessors
bool Game::isRunning() const
{
    return this->window->isOpen();
}

// Functions
void Game::pollEvents()
{
// Event polling
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
            // Event that is called when the close button is clicked
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                // Event that is called when the Escape button is pressed
                if (this->event.key.code == sf::Keyboard::Escape)
                {
                    window->close();
                }
                break;
            default:
                break;
        }
    }
    //idle animation
    if (clock.getElapsedTime().asSeconds() > .05f){
        character_position.left=(character_position.left+162)%1620;
        character_sprite.setTextureRect(character_position);
        clock.restart();
    }
}

void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    // Clear old frame
    window->clear();

    // Draw game
    window->draw(character_sprite);

    window->display();
    // Window is done drawing
}