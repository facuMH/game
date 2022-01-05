
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

	std::map<std::string, Button*> buttons;

	//Private Functions
    void initFonts(AssetsManager& am);
    void updateMousePositions(sf::RenderWindow * target);

public:
	PauseMenu(sf::RenderWindow* window, AssetsManager& am);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, const float y, const float width, const float height, const unsigned char_size, const std::string text);
	void update(sf::RenderWindow * target);
	void render(sf::RenderWindow *target);
};
