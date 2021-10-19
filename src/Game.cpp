#include <iostream>
#include "../headers/Game.h"

// Private functions
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    // load window configs from file
    std::ifstream ifs("../config/window.ini");

    // set default values
    std::string title = "none";
    this->videoMode.height = 480;
    this->videoMode.width = 640;
    unsigned int framerate_limit = 120;
    bool vertical_sync_enabled = false;

    // replace default configs with file contents
    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> this->videoMode.width >> this->videoMode.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }
    ifs.close();

    // create window
    this->window = new sf::RenderWindow(this->videoMode, title, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
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

void Game::updateDT()
{
    this->dt = this->dtClock.restart().asSeconds();
    std::cout << this->dt << "\n";
}
