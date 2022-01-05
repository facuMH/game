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
	background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	container.setSize(sf::Vector2f(static_cast<float>(currentSize.x) / 4.f,	static_cast<float>(currentSize.y) - p2pY(9.3f, vm)));
	container.setFillColor(sf::Color(20, 20, 20, 200));
	container.setPosition(static_cast<float>(currentSize.x) / 2.f - container.getSize().x / 2.f,	30.f);

	//Init text
	menuText.setFont(font);
	menuText.setFillColor(sf::Color(255, 255, 255, 200));
	menuText.setCharacterSize(calcCharSize(vm));
	menuText.setString("PAUSED");
	menuText.setPosition(	container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().width / 2.f,
    	container.getPosition().y + p2pY(4.f, vm)	);
}

PauseMenu::~PauseMenu()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void PauseMenu::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

std::map<std::string, Button*>& PauseMenu::getButtons()
{
	return buttons;
}

//Functions
const bool PauseMenu::isButtonPressed(const std::string key)
{
	return buttons[key]->isPressed();
}

void PauseMenu::addButton( const std::string key, const float y, const float width, const float height, const unsigned char_size, const std::string text)
{
	float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;

	buttons[key] = new Button(
		x, y, width, height,
		&font, text,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
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
		i.second->update(mousePosView);
	}
}

void PauseMenu::render(sf::RenderWindow * target)
{
	target->draw(background);
	target->draw(container);

	for (auto &i : buttons)
	{
		i.second->render(target);
	}

	target->draw(menuText);
}