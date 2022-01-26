#ifndef GAME_H
#define GAME_H
	
#include <iostream>
#include <stack>
#include <memory>
#include "SFML/Graphics.hpp"

#include "Types.hpp"
#include "Board.hpp"
#include "gui/Button.hpp"

//#include "states/IState.hpp"
#include "states/GameState.hpp"
#include "states/MenuState.hpp"

class Game  
{
private:
	const int width = 1280;
	const int height = 720;

	sf::RenderWindow* window;
	// new target for texture generation
	sf::View gameView;
	std::stack<std::shared_ptr<IState>> states;

public:
	Game();
	~Game();
	void run();

};

#endif