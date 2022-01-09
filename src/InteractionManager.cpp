#include "InteractionManager.h"

void InteractionManager::initDialogue(const Name& name) {
	if (name == "Old Man") {
		dialogues.emplace("Old Man", "Hello, Mr. Ninja! A bunch of aliens has taken this town!");
	}

}
