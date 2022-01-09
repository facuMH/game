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
	Texture* characterFaceTexture;
	sf::Sprite characterFaceSprite;
	sf::Font* font;
	sf::Text characterNameText;
	sf::Text dialogueText;
	AssetsManager assetsManager;
	InteractionManager interactionManager;

	// text animation
	std::string text;        // the text to draw (substring of the actual text since not all text is drawn at once)
	int text_pointer_length; // pointer to the position of the text to be drawn
	int text_pointer_start;
	float text_animation_timer;
	int drawn_line_counter;
	int arrow_motion_counter;
	sf::Vector2f arrow_motion_direction;
	bool max_display_lines_reached;
	bool text_is_finished = false;

	void cropTextToBox(std::string& new_text);
	static std::string getFaceTexturePath(const Name& characterName);

  public:
	DialogueBox() = default;
	DialogueBox(const Name& characterName, float dialogueYPosition);

	bool textDone() const;
	void setText(const std::string& characterName, std::string dialogueString);

	void update(const float& dt);
	void render(sf::RenderWindow* window);
};
