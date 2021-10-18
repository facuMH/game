//Using SDL and standard IO
#include <SFML/Graphics.hpp>
#undef main

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main() {

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "game", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event{};

    // Game loop
    while(window.isOpen()) {
        // Event polling
        while(window.pollEvent(event)) {
            switch(event.type) {
                // Event that is called when the close button is clicked
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    break;
            }
        }

        // Update

        // Render
        window.clear(sf::Color::White);     // Clear old frame

        // Draw game
        window.display();   // Window is done drawing
    }

    // End of application
    // SDL_Window* window = NULL;
    // SDL_Surface* screenSurface = NULL;

//    if (SDL_Init(SDL_INIT_VIDEO) < 0)
//    {
//        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//    }
    return 0;
}