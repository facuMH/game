#pragma once

#include <unordered_map>
#include "definitions.h"

class InteractionManager {
  public:
	DialogueArray getDialogues(const Name &name) {
		initDialogue(name);
		return dialogues.find(name)->second;
	}
	void initDialogue(Name name);
  private:
	// For each character, a dialogue array is saved
	std::unordered_map<Name, DialogueArray> dialogues;
};


