#pragma once

#include "AssetsManager.h"
#include "InteractionManager.h"
#include "definitions.h"

class DialogueBox {
  private:
	Position position;
	Texture* dialogueBoxTexture;
	sf::Sprite dialogueBoxSprite;
	Texture* arrowTexture;
	sf::Sprite arrowSprite;
	sf::Font* font;
	sf::Text characterNameText;
	sf::Text dialogueText;
	sf::RectangleShape shape;
	AssetsManager assetsManager;
	InteractionManager interactionManager;

	void cropTextToTextbox(std::string& new_text);

	// *** constants ***
	int POSITION_OFFSET;
	sf::Vector2f TEXT_POS_OFFSET;
	int MAX_TEXT_LINES;
	float TIME_UNTIL_NEXT_CHAR; // after this time the next char of the text is drawn
	sf::Vector2f NAME_TEXT_POS_OFFSET;
	sf::Vector2f ARROW_POS_OFFSET;

	// text animation
	std::string text;        // the text to draw (not the complete text needs to be drawn at once)
	int text_pointer_length; // points to the position of the text that should be drawn
	int text_pointer_start;
	float text_animation_timer;
	int drawn_line_counter;
	bool stop_typing_text;
	int arrow_motion_counter;
	bool arrow_up;
	sf::Vector2f arrow_motion_direction;
	bool text_is_finished = false;

  public:
	DialogueBox() = default;
	DialogueBox(const std::string& characterName, float windowHeight);

	bool textDone() const;
	void setText(const std::string& characterName, std::string dialogueString);

	void update(const float& dt);
	void render(sf::RenderWindow* window);
};
