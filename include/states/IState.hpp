#ifndef ISTATE_H
#define ISTATE_H

#include <memory>
#include <stack>

#include "SFML/Graphics.hpp"

class IState {
protected:
    sf::RenderWindow* window;
    bool pop = false;
    bool push = false;

public:
    //virtual IState(sf::RenderWindow* window) = 0;
    virtual ~IState() = 0;
    virtual void draw() = 0;
    // true  - IState unchanged
    // false - IState changed
    virtual void update() = 0;
    virtual bool stateChange(std::stack<std::shared_ptr<IState>>&) = 0;
};

#endif