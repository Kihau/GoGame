#include "Game.hpp"
#include "Random.hpp"

/*  TO DO LIST: 
-----------------------------------------------------------------------------
- Mechanics improvements:
    - Check if can capture other group before removing group itself
    - Prevent repetitions
    - Prevent suicide moves
- Game State:
    - Show points (taken white and black stones)
    - Button to disable/enable auto stone swap
    - Show in-game time
    - Reset board button
- Menu State:
    - Options
    - Exit 
    - Start game
    - About
    - Add more advanced things later on
- Add state system and move game login to GameState class
-----------------------------------------------------------------------------
    Event dispaching and updating
    1. Game class dispaches window events
    2. Input struct gets generated/modified
    3. Pass input struct to IState (and the to all its components)
*/

//#include "TestC/TestClass.hpp"

int countLen(char* cstring) {
    if (*cstring == '\0') return 0;
    return countLen(cstring + 1) + 1;
}

int main() {
    Random::init();

    {
        sf::RectangleShape rect(sf::Vector2f(100, 100));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(3.3f);
    }

    Game go_game;
    go_game.run();

    //std::cout << countLen("Hello") << "\n";

    //TestClass test;
    //std::cout << test.return_two();

    return 0;
}


