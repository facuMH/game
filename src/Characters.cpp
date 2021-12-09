#include <SFML/Window.hpp>

#include "Characters.h"

// if a weapon is already equipped it is swapped with the new one
// otherwise simply equips the new one
void Character::equip(Weapon* arms) {
	if(weapon != nullptr) {
		std::swap(weapon, arms);
		Position pos = animation.get_position();

		// TODO: check for a free Tile where you can actually drop the item.
		arms->drop(pos);
	} else {
		weapon = arms;
		arms = nullptr;
	}
}

// Move character up, down, left or right
void Character::move(const KeyAction key, sf::View* view) {
	constexpr float stepsize = 10.0f;
	animation.next();
	switch(key) {
	case KeyAction::LEFT:
		animation.sprite.move({-stepsize, 0.0f});
		if(animation.get_orientation().x > 0) {
			animation.mirror(animation.sprite.getLocalBounds().width);
		}
		view->setCenter(animation.sprite.getPosition());
		break;
	case KeyAction::RIGHT:
		animation.sprite.move({stepsize, 0.0f});
		if(animation.get_orientation().x < 0) {
			animation.mirror();
		}
		view->setCenter(animation.sprite.getPosition());
		break;
	case KeyAction::UP:
		animation.sprite.move({0.0f, -stepsize});
		view->setCenter(animation.sprite.getPosition());
		break;
	case KeyAction::DOWN:
		animation.sprite.move({0.0f, stepsize});
		view->setCenter(animation.sprite.getPosition());
		break;
	default: break;
	}
}