#ifndef ISTATE_H
#define ISTATE_H

#include "SFML/Graphics.hpp"

class IState : sf::Drawable {
protected:
    sf::RenderWindow* window;

public:
    //virtual IState(sf::RenderWindow* window) = 0;
    virtual ~IState() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual void update() = 0;
};

#endif