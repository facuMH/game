#include <iostream>

#include "Game.h"


// Private functions
void Game::initVariables()
{
    this->window = nullptr;
    // this->character_sprite= nullptr;
    // this->character_position= nullptr;
    // this->character_texture= nullptr;
}

void Game::initWindow()
{
    this->videoMode.height = 720;
    this->videoMode.width = 1280;

    this->window = new sf::RenderWindow(this->videoMode, "game", sf::Style::Titlebar | sf::Style::Close);

    // character_sprite = new sf::Sprite();
    // character_position = new Position(60,40,40,60);
    // character_texture= new sf::Texture;

    if (!character_texture.loadFromFile("../assets/character/Idle.png")){
        std::cout << "character not found in: " <<  "assets/character/Idle.png" << "\n";
    }
    character_texture.setSmooth(true);
    character_sprite.setTexture(character_texture);
    // character_position->x=60;
    // character_position->y=40;
    // character_position->x_offset=40;
    // character_position->y_offset=60;
    character_position.x=65;
    character_position.y=55;
    character_position.x_offset=40;
    character_position.y_offset=45;
    // character_sprite.setTextureRect(sf::IntRect(character_position->x, character_position->y,
    //                             character_position->x_offset, character_position->y_offset));
        character_sprite.setTextureRect(sf::IntRect(character_position.x, character_position.y,
                                character_position.x_offset, character_position.y_offset));
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
                //character_position->x= (character_position->x+160)%1620;
                character_position.x= (character_position.x+165)%1620;
                // character_sprite.setTextureRect(sf::IntRect(character_position->x, character_position->y,
                //                             character_position->x_offset, character_position->y_offset));
                character_sprite.setTextureRect(sf::IntRect(character_position.x, character_position.y,
                                character_position.x_offset, character_position.y_offset));
                //character_sprite.setPosition()
                break;
        }
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