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
    // load window configs from file
    std::ifstream ifs("../config/window.ini");

    // set default values
    std::string title = "RPG";
    unsigned int framerate_limit = 120;
    bool vertical_sync_enabled = false;

    // create window
    this->window = new sf::RenderWindow(this->videoMode, title, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);

    if (!character_texture_idle.loadFromFile("../assets/character/Idle.png")){
        std::cout << "character not found in: " <<  "assets/character/Idle.png" << "\n";
    }
    if (!character_texture_run.loadFromFile("../assets/character/Run.png")){
        std::cout << "character not found in: " <<  "assets/character/Run.png" << "\n";
    }

    character_position= sf::IntRect(65,55,45,50);
    character_texture_idle.setSmooth(true);
    character_sprite.setTexture(character_texture_idle);
    character_sprite.setTextureRect(character_position);
    character_sprite.scale(sf::Vector2f(3.f, 3.f)); 
    character_sprite.setPosition({50,50});
    std::cout << "First sprite set\n";

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
                } else if (this->event.key.code == sf::Keyboard::Right){
                    character_sprite.setTexture(character_texture_run);
                    character_position.left=(character_position.left+162)%1296;
                    character_sprite.setTextureRect(character_position);
                    if(character_sprite.getScale().x < 0 ) {
                        character_sprite.setOrigin({ 0, 0 });
                        character_sprite.scale({-1.f, 1.f});
                    }
                } else if (this->event.key.code == sf::Keyboard::Left){
                    character_sprite.setTexture(character_texture_run);
                    character_position.left=(character_position.left+162)%1296;
                    character_sprite.setTextureRect(character_position);
                    if(character_sprite.getScale().x > 0 ) {
                        character_sprite.setOrigin({ character_sprite.getLocalBounds().width, 0 });
                        character_sprite.scale({-1.f,1.f});
                    }
                }
                break;
            case sf::Event::MouseMoved:
                break;
            default:
                character_sprite.setTexture(character_texture_idle);
                character_position.left=(character_position.left+162)%1620;
                character_sprite.setTextureRect(character_position);
                clock.restart();
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
    window->draw(character_sprite);
    // Window is done drawing --> display result
    window->display();

}

void Game::updateDT()
{
    this->dt = this->dtClock.restart().asSeconds();
    //std::cout << "Time delta: " << this->dt << std::endl;
}

