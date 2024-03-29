#include "DialogueBox.h"
#include "AssetsPaths.h"
#include "definitions.h"
#include <sstream>

DialogueBox::DialogueBox(
    const Name& characterName, const std::string& faceTexturePath, const Position& dialoguePosition) {
	Texture* dialogueBoxTexture = assetsManager.getTexture(DIALOGUE_BOX_FACE.c);
	dialogueBoxSprite.setTexture(*dialogueBoxTexture);
	dialogueBoxSprite.setTextureRect(
	    sf::IntRect(0, 0, dialogueBoxTexture->getSize().x, dialogueBoxTexture->getSize().y));
	dialogueBoxSprite.setPosition(sf::Vector2f(dialoguePosition.x - dialogueBoxTexture->getSize().x / 2,
	    dialoguePosition.y - dialogueBoxTexture->getSize().y - Y_OFFSET_DIALOGUE_POSITION));

	Texture* arrowTexture = assetsManager.getTexture(DIALOGUE_ARROW.c);
	arrowSprite.setTexture(*arrowTexture);
	arrowSprite.setTextureRect(sf::IntRect(0, 0, arrowTexture->getSize().x, arrowTexture->getSize().y));
	arrowSprite.setPosition(dialogueBoxTexture->getSize().x / 2 - ARROW_POS_OFFSET.x + dialoguePosition.x,
	    dialoguePosition.y - ARROW_POS_OFFSET.y - Y_OFFSET_DIALOGUE_POSITION);

	sf::Font* font = assetsManager.getFont(DIALOGUE_FONT.c);

	characterNameText.setFont(*font);
	characterNameText.setCharacterSize(8);
	characterNameText.setFillColor(sf::Color::White);
	characterNameText.setPosition(dialogueBoxSprite.getPosition().x + CHARACTER_NAME_OFFSET.x,
	    dialogueBoxSprite.getPosition().y + CHARACTER_NAME_OFFSET.y);

	dialogueText.setFont(*font);
	dialogueText.setCharacterSize(12);
	dialogueText.setFillColor(sf::Color::Black);
	dialogueText.setPosition(
	    dialogueBoxSprite.getPosition().x + TEXT_POS_OFFSET.x, dialogueBoxSprite.getPosition().y + TEXT_POS_OFFSET.y);

	Texture* characterFaceTexture = assetsManager.getTexture(faceTexturePath);
	characterFaceSprite.setTexture(*characterFaceTexture);
	characterFaceSprite.setTextureRect(
	    sf::IntRect(0, 0, characterFaceTexture->getSize().x, characterFaceTexture->getSize().y));
	characterFaceSprite.setPosition(
	    dialogueBoxSprite.getPosition().x + FACE_OFFSET.x, dialogueBoxSprite.getPosition().y + FACE_OFFSET.y);
	setText(characterName, interactionManager.getDialogue(characterName));
}

void DialogueBox::update(const float& dt) {
	textAnimationTimer += dt;
	if(textAnimationTimer >= TIME_UNTIL_NEXT_CHAR) {
		textAnimationTimer = 0;
		// textToDraw to be drawn at this point of time
		dialogueText.setString(textToDraw.substr(drawTo, drawFrom + 1));

		// update textToDraw animation
		if(!maxDisplayLinesReached) {
			if(textToDraw.at(drawTo + drawFrom) == '\n') {
				if(++textLinesCounter >= MAX_TEXT_LINES) {
					maxDisplayLinesReached = true;
					arrowMotionCounter = 0;
					arrowMotionDirection = {0, -1};
				}
			}
			if(drawTo + drawFrom < textToDraw.size() - 1 && !maxDisplayLinesReached) {
				drawFrom++;
			} else {
				maxDisplayLinesReached = true;
			}
		} else {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				// if all textToDraw has been printed, the job is done
				if(drawTo + drawFrom >= textToDraw.size() - 1) {
					textIsFinished = true;
				} else {
					textLinesCounter = 0;
					drawTo += drawFrom + 1; // + 1 to skip one newline
					drawFrom = 0;
					maxDisplayLinesReached = false;
				}
			} else {
				// show arrow until space bar is pressed
				arrowMotionCounter++;
				if(arrowMotionCounter > 3) {
					arrowMotionDirection = {arrowMotionDirection.x * -1, arrowMotionDirection.y * -1};
					arrowMotionCounter = 0;
				}
				arrowSprite.move(arrowMotionDirection);
			}
		}
	}
}

void DialogueBox::render(sf::RenderWindow* window) {
	window->draw(dialogueBoxSprite);
	window->draw(dialogueText);
	window->draw(characterNameText);
	window->draw(characterFaceSprite);

	if(maxDisplayLinesReached) {
		window->draw(arrowSprite);
	}
}

// Helper function for splitting the dialogue string into words
std::vector<std::string> split(const std::string& s) {
	std::vector<std::string> words;
	std::istringstream ss(s);
	std::string word;
	while(ss >> word) {
		words.push_back(word);
	}
	return words;
}

// Helper function for cropping the text to match the size of the dialogue box
void DialogueBox::cropTextToBox(std::string& new_text) {
	if(!new_text.empty()) {
		std::vector<std::string> words = split(new_text);
		// base case with only one word and no whitespaces
		if(words.size() == 1) {
			new_text = words[0];
		} else {
			std::stringstream processed_text;
			std::stringstream tmp_text;
			tmp_text << words[0];
			words.erase(words.begin());
			for(const auto& t : words) {
				// add space and current word
				tmp_text << " " << t;
				dialogueText.setString(tmp_text.str());
				// true if textToDraw is bouncing out of the box
				if(dialogueText.getLocalBounds().width
				    < dialogueBoxSprite.getTexture()->getSize().x - TEXT_POS_OFFSET.x - DISTANCE_TEXT_TO_END_OF_BOX) {
					processed_text.str(std::string(""));
					processed_text << tmp_text.str();
				} else {
					processed_text << "\n" << t << std::flush;
					tmp_text.str(std::string(""));
					tmp_text << processed_text.str();
				}
			}
			new_text = processed_text.str();
		}
	}
	dialogueText.setString(std::string(""));
}

void DialogueBox::setText(const std::string& characterName, std::string dialogueString) {
	cropTextToBox(dialogueString);
	textToDraw = dialogueString;
	textAnimationTimer = 0.0;
	textLinesCounter = 0;
	drawFrom = 0;
	drawTo = 0;
	maxDisplayLinesReached = false;
	arrowMotionCounter = 0;
	arrowMotionDirection = {0, -1};
	textIsFinished = false;

	characterNameText.setString(characterName);
}

bool DialogueBox::textDone() const {
	return textIsFinished;
}
