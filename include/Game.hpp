#ifndef GAME_H
#define GAME_H
	
#include <iostream>
#include "SFML/Graphics.hpp"

#include "Types.hpp"
#include "Board.hpp"
#include "gui/Button.hpp"
#include "states/GameState.hpp"

class Game  
{
private:
	const int width = 1280;
	const int height = 720;

	std::unique_ptr<sf::RenderWindow> window;

	Button btn;
	Board board;

	// new target for texture generation
	sf::View gameView;

	sf::Texture bg_tex;
	sf::Sprite background;
	sf::Font font;

	f32 dt;

	sf::Texture wbag_tex;
	sf::Texture bbag_tex;
	sf::Sprite white_bag;
	sf::Sprite black_bag;

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