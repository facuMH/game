#pragma once

#include "AssetsManager.h"
#include "InteractionManager.h"
#include "definitions.h"

class DialogueBox {
  private:
	Position position;
	sf::Sprite dialogueBoxSprite;
	sf::Sprite arrowSprite;
	sf::Sprite characterFaceSprite;
	sf::Text characterNameText;
	sf::Text dialogueText;
	AssetsManager assetsManager;
	InteractionManager interactionManager;

	// text animation
	std::string textToDraw; // substring of the actual textToDraw since not all textToDraw is drawn at once
	int drawFrom;           // pointer to the position of the textToDraw to be drawn
	int drawTo;             // pointer to the first sign to be drawn
	float textAnimationTimer;
	int textLinesCounter;
	int arrowMotionCounter;
	sf::Vector2f arrowMotionDirection;
	bool maxDisplayLinesReached;
	bool textIsFinished = false;

	void cropTextToBox(std::string& new_text);

  public:
	DialogueBox() = default;
	DialogueBox(const Name& characterName, const std::string& faceTexturePath, float dialogueYPosition);

	bool textDone() const;
	void setText(const std::string& characterName, std::string dialogueString);

	void update(const float& dt);
	void render(sf::RenderWindow* window);
};
