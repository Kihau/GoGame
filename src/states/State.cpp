#include "states/State.hpp"

State::~State() {};

bool State::stateChange(std::stack<std::shared_ptr<State>>& states) {
    if (this->push != nullptr) {
        states.push(this->push);
        this->push = nullptr;
        //auto state = std::make_shared<GameState>(this->window);
        return true;
    } 

    if (this->pop) {
        this->pop = false;
        states.pop();
        return true;
    } 

    return false;
}

