#ifndef GAME_H
#define GAME_H
	
#include "SFML/Graphics.hpp"

class Game  
{
private:
	const int width = 1280;
	const int height = 720;
	sf::RenderWindow* window;
	sf::Sprite board;
	sf::Texture tex;
	float dt;

private:
	void render();
	void update();

public:
	Game();
	~Game();
	void run();

};

#endif