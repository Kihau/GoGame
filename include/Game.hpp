#ifndef GAME_H
#define GAME_H
	
#include "SFML/Graphics.hpp"

class Game  
{
private:
	sf::RenderWindow* window;
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