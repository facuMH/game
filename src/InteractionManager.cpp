#include "InteractionManager.h"

void InteractionManager::initDialogue(const Name& name) {
	if(name == "Old Man") {
		dialogues.emplace(name, "Hello, Mr. Ninja! A bunch of aliens has taken this town! One of them even ate my "
		                             "wife and now they hide in our houses. What are you going to do about it? ");
	} else if (name == "Egg Girl") {
		dialogues.emplace(name, "Help me! A monster is in my house and stole all my toys!");
	} else if (name == "Princess") {
		dialogues.emplace(name, "This is the worst day of my life!");
	}
}
