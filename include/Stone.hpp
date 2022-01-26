#ifndef STONE_H
#define STONE_H

enum State {
    None = 0,
    White = 1,
    Black = 2,
};

// sf::Color getColor(State state) {
//     switch (state)
//     {
//     case 0: return sf::Color(sf::Color::Transparent);
//     case 1: return sf::Color(sf::Color::White);
//     case 2: return sf::Color(sf::Color::Black);
//     default: return sf::Color(sf::Color::Transparent);
//     }
// } 

#include "Types.hpp"
#include "SFML/Graphics.hpp"

struct Stone {
    /// TODO: Make this an enum
    // -1 - unplacable (custom maps)
    // 0  - empty
    // 1  - black
    // 2  - white
    i32 turn;
    sf::Sprite sprite;
};


#endif