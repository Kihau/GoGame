#include "Game.hpp"
#include "Random.hpp"

/*  TO DO LIST: 
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
*/

int main() {
    Random::init();

    Game go_game;
    go_game.run();
    return 0;
}
