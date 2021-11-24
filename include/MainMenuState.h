
#pragma once


#include "GameState.h"
#include "Button.h"

class MainMenuState :
    public State
{
private:

    // Variable
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, Button*> buttons;

    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

    virtual ~MainMenuState();

    // Functions
    void endState();

    void updateInput(const float& dt);
    void updateButtons();
    void renderButtons(sf::RenderTarget* target = nullptr);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);

	void updateKeybinds(const float &dt) override;
	void quitStateActions() override;
	void checkIfQuitting() override;
};
