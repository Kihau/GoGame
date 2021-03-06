#ifndef ISTATE_H
#define ISTATE_H

#include <memory>
#include <stack>

#include "SFML/Graphics.hpp"

class State {
protected:
    sf::RenderWindow* window;
    bool pop = false;
    std::shared_ptr<State> push = nullptr;

public:
    //virtual IState(sf::RenderWindow* window) = 0;
    virtual ~State() = 0;
    virtual void draw() = 0;
    // true  - IState unchanged
    // false - IState changed
    virtual void update(const std::vector<sf::Event>&, sf::Time) = 0;
    virtual bool stateChange(std::stack<std::shared_ptr<State>>&);
};

#endif