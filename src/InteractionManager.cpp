#include "InteractionManager.h"

void InteractionManager::initDialogue(Name name) {
	DialogueArray dialogue;
	if (name == "Old Man") {
		dialogue.push_back("Old Man: Hello, Mr. Ninja! A bunch of aliens has taken this town!");
		dialogue.push_back("You: Oh no! How could that happen?");
		dialogue.push_back("Old Man: We don't know but they've eaten my wife!");
	}
	dialogues.emplace(name, dialogue);
}
