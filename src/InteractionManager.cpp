#include "InteractionManager.h"

void InteractionManager::initDialogue(const Name& name) {
	if(name == "Old Man") {
		dialogues.emplace(
		    name, "Hello, Mr. Ninja! A bunch of aliens has taken this town! They even ate my wife and now they hide in "
		          "our houses. Each alien has eaten one of her body parts. Only if you can defeat all of them, we "
		          "might get them back, so that we can be together again! You're my last hope!");
	} else if(name == "Egg Girl") {
		dialogues.emplace(name, "Help me! A monster is in my house and stole all my toys!");
	} else if(name == "Princess") {
		dialogues.emplace(name, "This is the worst day of my life!");
	}
}
