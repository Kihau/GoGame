#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "states/IState.hpp"

class GameState : public IState {
public:
    GameState(sf::RenderWindow*);
    void draw(sf::RenderTarget&, sf::RenderStates) const;
    void update();
};

#endif