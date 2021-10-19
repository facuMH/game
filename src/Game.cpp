#include <iostream>
#include "headers/Game.h"

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

void Game::initStates()
{
    this->states.push(new GameState(this->window));
}

// Constructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initStates();
}

// Destructor
Game::~Game()
{
    // Delete window
    delete this->window;

    // Clear states stack
    while (!this->states.empty())
    {
        // remove data
        delete this->states.top();
        // remove pointer
        this->states.pop();
    }
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

    if (!this->states.empty())
    {
        // update current game state
        this->states.top()->update(this->dt);
    }
}

void Game::render()
{
    // Clear old frame
    window->clear();

    // Draw game
    if (!this->states.empty())
    {
        // render current game state
        this->states.top()->render(this->window);
    }

    // Window is done drawing --> display result
    window->display();

}

void Game::updateDT()
{
    this->dt = this->dtClock.restart().asSeconds();
    std::cout << "Time delta: " << this->dt << std::endl;
}

