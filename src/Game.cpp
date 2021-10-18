#include "Game.h"

// Private functions
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode.height = 480;
    this->videoMode.width = 640;

    this->window = new sf::RenderWindow(this->videoMode, "game", sf::Style::Titlebar | sf::Style::Close);
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

    window->display();
    // Window is done drawing
}