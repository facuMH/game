#include "State.h"
#include <AssetsPaths.h>


State::State(sf::RenderWindow* renderWindow) {
	window = renderWindow;
}
void State::drawDialogue(sf::RenderWindow* window, AssetsManager assetsManager, sf::Text text) {
	sf::Sprite dialogueBox;
	Texture* dialogueBoxTexture = assetsManager.getTexture(DIALOGUE_BOX.c);
	dialogueBox.setTexture(*dialogueBoxTexture);
	dialogueBox.setPosition(100.0f, 100.f);
	window->draw(dialogueBox);
	window->draw(text);
}


State::~State() = default;