#include "MainMenuState.h"



MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
    : State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();

	this->initButtons();
}

void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if(!this->backgroundTexture.loadFromFile("../assets/MainMenu/Background.jpeg"))
	{
		throw"Error::MainMENUSTATE::FAILED TO LOAD BACKGROUND TEXTURE";
	}


	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("../Fonts/Dosis-Light.ttf"))
	{
		throw("Could not load font");
	}

}

void MainMenuState::initKeybinds()
{

	std::ifstream ifs("../config/mainmenustate_keysbind.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	/*

	ifs.close();

	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");*/

}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(300, 480, 150, 50, &this->font, "New Game", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["SETTINGS"] = new Button(300, 580, 150, 50, &this->font, "Settings", sf::Color(70, 70, 70, 200), sf::Color(100, 100, 100, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT"] = new Button(300, 680, 150, 50, &this->font, "QUIT", sf::Color(70, 70, 70, 200), sf::Color(100, 100, 100, 255), sf::Color(20, 20, 20, 200));
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();

	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}



void MainMenuState::endState()
{
	std::cout << "Ending Maun Menu!" << "\n";
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkIfQuitting();



}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handels their functionality*/

	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	// New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	// Quit the game
	if (this->buttons["EXIT"]->isPressed())
	{
		this->quit = true;
	}
}


void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();


	//this->gamestate_btn->update(this->mousePosView);

}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}


void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->renderButtons(target);

	// Remove Later!!!!!
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y -50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(19);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}

void MainMenuState::checkIfQuitting()
{ State::checkIfQuitting(); }

void MainMenuState::updateKeybinds(const float &dt)
{ this->checkIfQuitting(); }

void MainMenuState::quitStateActions()
{
	std::cout << "Ending current game state" << std::endl;
}
