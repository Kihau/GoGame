#ifndef GAME_H
#define GAME_H
	
#include <iostream>
#include "SFML/Graphics.hpp"

#include "Types.hpp"
#include "Board.hpp"

class Game  
{
private:
	const int width = 1280;
	const int height = 720;

	std::unique_ptr<sf::RenderWindow> window;

	Board board;

	// new target for texture generation
	sf::View gameView;

	sf::Texture bg_tex;
	sf::Sprite background;

	f32 dt;

private:
	void render();
	void update();
	void dispatchEvents();
	void log();

public:
	Game();
	~Game();
	void run();

};

#endif