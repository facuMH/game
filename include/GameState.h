#ifndef RPG_GAMESTATUS_H
#define RPG_GAMESTATUS_H

#include "State.h"
class GameState: public State
{
public:
    // Constructor
    GameState(sf::RenderWindow *window);
    // Destructor
    ~GameState() override;

    // Functions
    void update(const float& dt) override;
    void render(sf::RenderTarget* target) override;
    void endState() override;
};


#endif //RPG_GAMESTATUS_H
