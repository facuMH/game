#include <iostream>

#include "Game.h"
#include <fstream>


// Private functions
void Game::initVariables()
{
    this->window = nullptr;

    if (!character_texture_idle.loadFromFile("../assets/character/Idle.png")) {
        std::cout << "character not found in: " <<  "assets/character/Idle.png" << "\n";
    }
    if (!character_texture_run.loadFromFile("../assets/character/Run.png")){
        std::cout << "character not found in: " <<  "assets/character/Run.png" << "\n";
    }

    player = Character("Adventurer", Stats(15, 20, 50, 30),
                        Animation("../assets/character/Idle.png", sf::IntRect(65, 55, 45, 50), Interval(162,0), Position(50,50))
                        );
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

  // replace default configs with file contents
  if (ifs.is_open()) {
    std::getline(ifs, title);
    ifs >> this->videoMode.width >> this->videoMode.height;
    ifs >> framerate_limit;
    ifs >> vertical_sync_enabled;
  }
  ifs.close();

  // create window
  this->window = new sf::RenderWindow(this->videoMode, title,
                                      sf::Style::Titlebar | sf::Style::Close);
  this->window->setFramerateLimit(framerate_limit);
  this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
    this->states.push(new GameState(this->window));
}

// Constructor
Game::Game() {
  this->initVariables();
  this->initWindow();
  this->initStates();
}

// Destructor
Game::~Game() {
  // Delete window
  delete this->window;

  // Clear states stack
  while (!this->states.empty()) {
    // remove data
    delete this->states.top();
    // remove pointer
    this->states.pop();
  }
}

// Accessors
bool Game::isRunning() const { return this->window->isOpen(); }

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

                    // this should become much simpler with new Class Player
                }
                else if (this->event.key.code == sf::Keyboard::Right){
                    player.animation.set_texture(character_texture_run);
                    player.animation.next();
                    if(player.animation.get_orientation().x < 0 ) {
                        player.animation.mirror();
                    }
                } else if (this->event.key.code == sf::Keyboard::Left){
                    player.animation.next();
                    if(player.animation.get_orientation().x > 0 ) {
                        player.animation.mirror(player.animation.sprite.getLocalBounds().width);
                    }
                }
                break;
            case sf::Event::MouseMoved:
                break;
            default:
                player.animation.set_texture(character_texture_idle);
                player.animation.next();
                clock.restart();
                break;
        }
    }
    //idle animation
    if (clock.getElapsedTime().asSeconds() > .05f){
        player.animation.next();
        clock.restart();
    }
}

void Game::update() {
  this->pollEvents();

  if (!this->states.empty()) {
    // update current game state
    this->states.top()->update(this->dt);
    // check if the state is about to be quit
    if (this->states.top()->isQuit()) {
      // quit actions
      this->states.top()->quitStateActions();
      delete this->states.top();
      this->states.pop();
    }
  }

  // End of application
  else {
    // Since the game depends on the window being open (see function
    // isRunning()), closing the window ends the game
    this->endApplication();
    this->window->close();
  }
}

void Game::render() {
  // Clear old frame
  window->clear();

    // Draw game
    if (!this->states.empty())
    {
        // render current game state
        this->states.top()->render(this->window);
    }
    window->draw(player.animation.sprite);
    // Window is done drawing --> display result
    window->display();

}

void Game::updateDT() {
  this->dt = this->dtClock.restart().asSeconds();
  // std::cout << "Time delta: " << this->dt << std::endl;
}

void Game::endApplication() { std::cout << "Ending application" << std::endl; }
