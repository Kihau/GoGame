#include "Game.hpp"
#include "Random.hpp"

#include "Types.hpp"
#include "Stats.hpp"
#include "Settings.hpp"

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

class Thingy {
public:
    int num;
    Thingy(bool epic_flag, int num) {
        this->num = num;

        if (epic_flag)
            *this = Thingy(false, 23);
    }
};

#include <math.h>
#include <iostream>
#include <fstream>

/* TESTING - TO DO
    - [x] Zapis planszy - binary
    - [x] Zapis wygladu planszy
    - [x] Opcje
    - [x] Statystyki
*/

// Settings:
//  - enable sounds
//  - fixed fps (on/off)
//  - logging
//  - show fps

int main() {
    Random::init();

    Settings::load();

    if (!Stats::load()) {
        std::cerr << "Failed to load stats, values reset to defaults\n";
    }

    Game go_game;
    go_game.run();

    // save stats every 15 minutes?
    Stats::save();
    Settings::save();
    
    return 0;
}


