
#include "Characters.h"

// if a weapon is already equipped it is swapped with the new one
// otherwise simply equips the new one
void Character::equip(Weapon *arms) {
  if (weapon != nullptr) {
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
void Character::move(const sf::Keyboard::Key key) {
    constexpr float stepsize = 10.0f;
    animation.next();
    switch (key) {
        case sf::Keyboard::Left:
            animation.sprite.move({-stepsize, 0.0f});
            if (animation.get_orientation().x > 0) {
                animation.mirror(animation.sprite.getLocalBounds().width);
            }
            break;
        case sf::Keyboard::Right:
            animation.sprite.move({stepsize, 0.0f});
            if (animation.get_orientation().x < 0) {
                animation.mirror();
            }
            break;
        case sf::Keyboard::Up:
            animation.sprite.move({0.0f, -stepsize});
            break;
        case sf::Keyboard::Down:
            animation.sprite.move({0.0f, stepsize});
            break;
        default:
            break;
    }
}