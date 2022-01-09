#include "AssetsManager.h"
#include "AssetsPaths.h"
#include "PauseMenu.h"
#include "State.h"

PauseMenu::PauseMenu(sf::RenderWindow* window, AssetsManager& am)
{
    initFonts(am);

    sf::Vector2u currentSize = window->getSize();
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	//Init background
	background.setSize(sf::Vector2f(static_cast<float>(currentSize.x),	static_cast<float>(currentSize.y)));
	background.setFillColor(sf::Color(200, 200, 200, 255));

	//Init container
	container.setSize(sf::Vector2f(static_cast<float>(currentSize.x) / 4.f,	static_cast<float>(currentSize.y) / 2.f));
	container.setFillColor(sf::Color(120, 120, 120, 255));
	container.setPosition(static_cast<float>(currentSize.x) / 2.f - container.getSize().x / 2.f, 30.f);

	//Init text
	menuText.setFont(font);
	menuText.setFillColor(sf::Color(255, 255, 255, 255));
	menuText.setCharacterSize(20);
	menuText.setString("PAUSED");
	menuText.setPosition(container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().width / 2.f, container.getPosition().y);

	//Button(400, 100, 150, 50, &font, "QUIT", GREY, LIGHTGREY, sf::Color::Black)
	float x = container.getPosition().x + container.getSize().x / 2.f - 50.f;
	buttons.push_back(Button(x, 100, 150, 50, &font, "QUIT", GREY, LIGHTGREY, sf::Color::Black));
	
}

PauseMenu::~PauseMenu() { }

void PauseMenu::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

//Functions
const bool PauseMenu::isCloseButtonPressed()
{
	return buttons[0].isPressed();
}

void PauseMenu::updateMousePositions(sf::RenderWindow * window)
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePoseWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePoseWindow);
}

void PauseMenu::update(sf::RenderWindow * target)
{
    updateMousePositions(target);
	for (auto &i : buttons)
	{
		i.update(mousePosView);
	}
}

void PauseMenu::render(sf::RenderWindow * target)
{
	target->draw(background);
	target->draw(container);

	for (auto &i : buttons)
	{
		i.render(target);
	}

	target->draw(menuText);
}