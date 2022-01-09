#include "DialogueBox.h"
#include "AssetsPaths.h"
#include "definitions.h"
#include <sstream>

DialogueBox::DialogueBox(const Name& characterName, float dialogueYPosition) {

	dialogueBoxTexture = assetsManager.getTexture(DIALOGUE_BOX_FACE.c);

	dialogueBoxSprite.setTexture(*dialogueBoxTexture);
	dialogueBoxSprite.setTextureRect(sf::IntRect(0, 0, int(dialogueBoxTexture->getSize().x), int(dialogueBoxTexture->getSize().y)));
	dialogueBoxSprite.setPosition(sf::Vector2f(
	    float(POSITION_OFFSET), float(dialogueYPosition - dialogueBoxTexture->getSize().y + POSITION_OFFSET)));

	arrowTexture = assetsManager.getTexture(DIALOGUE_ARROW.c);

	arrowSprite.setTexture(*arrowTexture);
	arrowSprite.setTextureRect(sf::IntRect(0, 0, int(arrowTexture->getSize().x), int(arrowTexture->getSize().y)));
	arrowSprite.setPosition(
	    float(dialogueBoxTexture->getSize().x) - ARROW_POS_OFFSET.x, dialogueYPosition - ARROW_POS_OFFSET.y);

	font = assetsManager.getFont(DIALOGUE_FONT.c);

	characterNameText.setFont(*font);
	characterNameText.setCharacterSize(12);
	characterNameText.setFillColor(sf::Color::White);
	characterNameText.setPosition(
	    dialogueBoxSprite.getPosition().x + CHARACTER_NAME_OFFSET.x, dialogueBoxSprite.getPosition().y + CHARACTER_NAME_OFFSET.y);

	dialogueText.setFont(*font);
	dialogueText.setCharacterSize(12);
	dialogueText.setFillColor(sf::Color::Black);
	dialogueText.setPosition(dialogueBoxSprite.getPosition().x + TEXT_POS_OFFSET.x, dialogueBoxSprite.getPosition().y + TEXT_POS_OFFSET.y);

	characterFaceTexture = assetsManager.getTexture(getFaceTexturePath(characterName));
	characterFaceSprite.setTexture(*characterFaceTexture);
	characterFaceSprite.setTextureRect(sf::IntRect(0, 0, characterFaceTexture->getSize().x, characterFaceTexture->getSize().y));
	characterFaceSprite.setPosition(dialogueBoxSprite.getPosition().x + FACE_OFFSET.x, dialogueBoxSprite.getPosition().y + FACE_OFFSET.y);
	setText(characterName, interactionManager.getDialogue(characterName));
}

void DialogueBox::update(const float& dt) {
	text_animation_timer += dt;
	if(text_animation_timer >= TIME_UNTIL_NEXT_CHAR) {
		text_animation_timer = 0;
		// text to be drawn at this point of time
		dialogueText.setString(text.substr(text_pointer_start, text_pointer_length + 1));

		// update text animation
		if(!max_display_lines_reached) {
			if(text.at(text_pointer_start + text_pointer_length) == '\n') {
				if(++drawn_line_counter >= MAX_TEXT_LINES) {
					max_display_lines_reached = true;
					arrow_motion_counter = 0;
					arrow_motion_direction = {0, -1};
				}
			}
			if(text_pointer_start + text_pointer_length < text.size() - 1 && !max_display_lines_reached) {
				text_pointer_length++;
			} else {
				max_display_lines_reached = true;
			}
		} else {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

				// if all text has been printed, the job is done
				if(text_pointer_start + text_pointer_length >= text.size() - 1) {
					text_is_finished = true;
				} else {
					drawn_line_counter = 0;
					text_pointer_start += text_pointer_length + 1; // + 1 to skip one newline
					text_pointer_length = 0;
					max_display_lines_reached = false;
				}
			} else {
				// show arrow until space bar is pressed
				arrow_motion_counter++;
				if(arrow_motion_counter > 3) {
					arrow_motion_direction = {arrow_motion_direction.x * -1, arrow_motion_direction.y * -1};
					arrow_motion_counter = 0;
				}
				arrowSprite.move(arrow_motion_direction);
			}
		}
	}
}

void DialogueBox::render(sf::RenderWindow* window) {
	window->draw(dialogueBoxSprite);
	window->draw(dialogueText);
	window->draw(characterNameText);
	window->draw(characterFaceSprite);

	if(max_display_lines_reached) {
		window->draw(arrowSprite);
	}
}

// Helper function for splitting the dialogue string into words
std::vector<std::string> split(const std::string& s) {
	std::vector<std::string> words;
	std::istringstream ss(s);
	std::string word;
	while (ss >> word) {
		words.push_back(word);
	}
	return words;
}

void DialogueBox::cropTextToBox(std::string& new_text) {
	if(!new_text.empty()) {
		std::vector<std::string> words = split(new_text);
		// base case with only one word and no whitespace
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
				// true if text is bouncing out of the box
				if(dialogueText.getLocalBounds().width < float(dialogueBoxTexture->getSize().x - TEXT_POS_OFFSET.x + POSITION_OFFSET) - TEXT_POS_OFFSET.y * 2) {
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
	text = dialogueString;
	text_animation_timer = 0.0;
	drawn_line_counter = 0;
	text_pointer_length = 0;
	text_pointer_start = 0;
	max_display_lines_reached = false;
	arrow_motion_counter = 0;
	arrow_motion_direction = {0, -1};
	text_is_finished = false;

	characterNameText.setString(characterName);
}

bool DialogueBox::textDone() const {
	return text_is_finished;
}
std::string DialogueBox::getFaceTexturePath(const Name& characterName) {
	if (characterName == "Old Man") {
		return OLD_MAN_FACE.c;
	} else if (characterName == "Egg Girl") {
		return EGG_GIRL_FACE.c;
	} else if (characterName == "Princess") {
		return PRINCESS_FACE.c;
	}
}
