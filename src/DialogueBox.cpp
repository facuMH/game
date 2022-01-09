#include "DialogueBox.h"
#include "AssetsPaths.h"
#include <sstream>

DialogueBox::DialogueBox(const std::string& characterName, float windowHeight) {

	POSITION_OFFSET = 10;
	TEXT_POS_OFFSET = {30, 60};
	MAX_TEXT_LINES = 5;
	TIME_UNTIL_NEXT_CHAR = 0.05; // after this time the next character of the text is drawn
	NAME_TEXT_POS_OFFSET = {10, -2};
	ARROW_POS_OFFSET = {30, 30};

	dialogueBoxTexture = assetsManager.getTexture(DIALOGUE_BOX.c);
	shape.setTextureRect(sf::IntRect(0, 0, int(dialogueBoxTexture->getSize().x), int(dialogueBoxTexture->getSize().y)));
	shape.setPosition(sf::Vector2f(float(POSITION_OFFSET), float(windowHeight - dialogueBoxTexture->getSize().y - POSITION_OFFSET)));
	dialogueBoxSprite.setTexture(*dialogueBoxTexture);
	dialogueBoxSprite.setTextureRect(shape.getTextureRect());
	dialogueBoxSprite.setPosition(shape.getPosition());

	arrowTexture = assetsManager.getTexture(DIALOGUE_ARROW.c);
	arrowSprite.setTexture(*arrowTexture);
	arrowSprite.setTextureRect(sf::IntRect(0, 0, int(arrowTexture->getSize().x), int(arrowTexture->getSize().y)));
	arrowSprite.setPosition(
	    POSITION_OFFSET + shape.getSize().x - ARROW_POS_OFFSET.x, windowHeight - POSITION_OFFSET - ARROW_POS_OFFSET.y);

	font = assetsManager.getFont(DIALOGUE_FONT.c);

	characterNameText.setFont(*font);
	characterNameText.setCharacterSize(12);
	characterNameText.setFillColor(sf::Color::White);
	characterNameText.setPosition(
	    shape.getPosition().x + NAME_TEXT_POS_OFFSET.x, shape.getPosition().y + NAME_TEXT_POS_OFFSET.y);

	dialogueText.setFont(*font);
	dialogueText.setCharacterSize(14);
	dialogueText.setFillColor(sf::Color::Black);
	dialogueText.setPosition(shape.getPosition().x + TEXT_POS_OFFSET.x, shape.getPosition().y + TEXT_POS_OFFSET.y);

	setText(characterName, "");
}

void DialogueBox::update(const float& dt) {
	text_animation_timer += dt;
	if(text_animation_timer >= TIME_UNTIL_NEXT_CHAR) {
		text_animation_timer = 0;
		dialogueText.setString(text.substr(text_pointer_start, text_pointer_length + 1));

		// update text animation
		if(!stop_typing_text) {
			// consider max line limit
			if(text.at(text_pointer_start + text_pointer_length) == '\n') {
				if(++drawn_line_counter >= MAX_TEXT_LINES) {
					stop_typing_text = true;
					arrow_motion_counter = 0;
					arrow_motion_direction = {0, -1};
				}
			}
			if(text_pointer_start + text_pointer_length < text.size() - 1 && !stop_typing_text) {
				text_pointer_length++;
			} else {
				stop_typing_text = true;
			}
		} else {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				// blink until key pressed, then do the following
				// close textbox if text is done
				if(text_pointer_start + text_pointer_length >= text.size() - 1) {
					// indicate that the job of the textbox is done
					text_is_finished = true;
				} else {
					drawn_line_counter = 0;
					text_pointer_start += text_pointer_length + 1; // +1 to skip one newline
					text_pointer_length = 0;
					stop_typing_text = false;
				}
			} else {
				// show blinking arrow
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
	window->draw(shape);
	window->draw(dialogueBoxSprite);
	window->draw(dialogueText);
	window->draw(characterNameText);
	if(stop_typing_text) {
		window->draw(arrowSprite);
	}
}

// Helper function for splitting the dialogue string into words
std::vector<std::string> split(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::stringstream tokenStream(s);
	while(std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void DialogueBox::cropTextToTextbox(std::string& new_text) {
	if(!new_text.empty()) {
		std::vector<std::string> token = split(new_text, ' ');
		// base case with only one word and no whitespace
		if(token.size() == 1) {
			new_text = token[0];
		} else {
			std::stringstream processed_text;
			std::stringstream tmp_text;
			tmp_text << token[0];
			token.erase(token.begin());
			for(const auto& t : token) {
				tmp_text << " " << t << std::flush;
				dialogueText.setString(tmp_text.str());
				// true if text is bouncing out of the box
				if(dialogueText.getLocalBounds().width < shape.getSize().x - TEXT_POS_OFFSET.y * 2) {
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
	cropTextToTextbox(dialogueString);
	text = dialogueString;
	text_animation_timer = 0.0;
	drawn_line_counter = 0;
	text_pointer_length = 0;
	text_pointer_start = 0;
	stop_typing_text = false;
	arrow_motion_counter = 0;
	arrow_motion_direction = {0, -1};
	text_is_finished = false;

	characterNameText.setString(characterName);
}

bool DialogueBox::textDone() const {
	return stop_typing_text;
}
