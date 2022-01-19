#include "Game.hpp"  
	
Game::Game()
{
    this->dt = 0.0f;
    this->window = new sf::RenderWindow(sf::VideoMode(1200, 800), "GoGame by Kihau");
}
	
Game::~Game()
{
	delete this->window;
}

void Game::run() {
    while(this->window->isOpen()) {
        //this->update();
        //this->render();
    }
}