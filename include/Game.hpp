#ifndef GAME_H
#define GAME_H
	
#include <iostream>
#include "SFML/Graphics.hpp"

#include "Board.hpp"

class Game  
{
private:
	// true - white, false - black
	bool player = true;
	const int width = 1280;
	const int height = 720;
	std::unique_ptr<sf::RenderWindow> window;

	// new target for texture generation
	sf::RenderTexture target;

	sf::Sprite bg;
	sf::Texture tex;

	sf::Sprite board;
	sf::Texture tex2;

	sf::Sprite white;
	sf::Texture tex3;

	int dots[19][19] = {};

	float dt;

private:
	void render();
	void update();
	void log();

public:
	Game();
	~Game();
	void run();

};

#endif