#ifndef STATSSTATE_H
#define STATSSTATE_H

#include <iostream>

#include "SFML/Window.hpp"
#include "states/State.hpp"
#include "Stats.hpp"

class StatsState : public State {
private: 
    sf::Texture bg_tex;
	sf::Sprite background;

    sf::Font font;
    std::vector<sf::Text> buttons;
    sf::Text back_btn;
    
public:
    StatsState(sf::RenderWindow* window);
    void draw();
    void update(const std::vector<sf::Event>&, sf::Time);
};

#endif