#ifndef GAME_H
#define GAME_H
	
#include <iostream>
#include <stack>
#include <memory>
#include <iomanip>
#include "SFML/Graphics.hpp"

#include "Types.hpp"
#include "Board.hpp"
#include "gui/Button.hpp"

#include "Stats.hpp"
#include "Settings.hpp"

//#include "states/IState.hpp"
#include "states/GameState.hpp"
#include "states/MenuState.hpp"

#include "Animation.hpp"

class Game  
{
private:
	const i32 width = 1280;
	const i32 height = 720;

	sf::RenderWindow* window;
	// new target for texture generation
	sf::View gameView;
	std::stack<std::shared_ptr<State>> states;
	std::vector<sf::Event> events;

	sf::Clock gameClock;
	sf::Time deltaTime;
	sf::Time prevTime;
	sf::Time totalTime;

	const i32 log_delay = 500;
	sf::Time logTime;

	sf::Font fps_font;
	sf::Text fps;

private:
	void dispatchEvents();
	void logEvents();

public:
	Game();
	~Game();
	void run();

};

#endif