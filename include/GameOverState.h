#pragma once

#include "AssetsManager.h"
#include "State.h"
class GameOverState : public State {


  private:
	sf::View view;
	sf::RectangleShape background;
	sf::Font font;
	sf::SoundBuffer soundBuffer;
	sf::Sound blipSound;
	sf::Music music;
	KeyList* supportedKeys;

	Buttons buttons;

	// Functions
	void initBackground(sf::RenderWindow* window, AssetsManager& am);
	void initFonts(AssetsManager& am);

  public:
	GameOverState(sf::RenderWindow* window, AssetsManager& am, KeyList* supportedKeys);
	~GameOverState() override;

	// Functions
	void update(const float& dt) override;
	void render(sf::RenderWindow* window) override;
	StateAction handleKeys(sf::Keyboard::Key key) override;
	void updateKeybinds(const float& dt) override;
	void quitStateActions() override;
	bool shouldQuit() override;
	Position getCurrentPlayerPosition() override { return {0, 0}; };
	void drawPlayer(sf::RenderWindow* window) override;
	sf::View getView() override { return view; };
	StateAction shouldAct() override;
	void stopMusic() override;
	void resumeMusic() override;

};
