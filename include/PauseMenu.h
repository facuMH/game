
#pragma once

#include "Button.h"
#include "definitions.h"

class PauseMenu
{
private:
	sf::Font font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePoseWindow;
	sf::Vector2f mousePosView;

	Buttons buttons;

	//Private Functions
    void initFonts(AssetsManager& am);
    void updateMousePositions(sf::RenderWindow * target);

public:
	PauseMenu(sf::RenderWindow* window, AssetsManager& am);
	virtual ~PauseMenu();

	//Functions
	const bool isCloseButtonPressed();
	void update(sf::RenderWindow * target);
	void render(sf::RenderWindow *target);
};
