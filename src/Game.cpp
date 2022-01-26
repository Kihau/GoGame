#include "Game.hpp"

Game::Game()
{
    this->window = new sf::RenderWindow(
        sf::VideoMode(width, height), 
        "GoGame by Kihau"
    );
    this->window->setFramerateLimit(60);

    this->gameView = sf::View(sf::FloatRect(0, 0, 1920.0f, 1080.0f));
    this->window->setView(gameView);   

    auto init_state = std::make_shared<MenuState>(this->window);
    this->states.push(init_state);
}

Game::~Game() { 
    delete this->window;
}

void Game::run() {
    while(this->window->isOpen() && !this->states.empty()) {

        this->states.top()->update();

        if (this->states.top()->stateChange(this->states))
            continue;

        this->window->clear(sf::Color::Black);
        this->states.top()->draw();
        this->window->display();
    }
}