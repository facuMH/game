#ifndef RPG_GAMESTATE_H
#define RPG_GAMESTATE_H

#include "State.h"
class GameState: public State
{
public:
    // Constructor
    explicit GameState(sf::RenderWindow *window);
    // Destructor
    ~GameState() override;

    // Functions
    void update(const float& dt) override;
    void render(sf::RenderTarget* target) override;
    void updateKeybinds(const float& dt) override;
    void checkIfQuitting() override;
    void quitStateActions() override;
};


#endif //RPG_GAMESTATE_H
