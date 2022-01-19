#include "Game.hpp"

Game::Game()
{
    this->dt = 0.0f;
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), "GoGame by Kihau");
    this->tex.loadFromFile("resources/textures/go.png", sf::IntRect(0, 0, 1920, 1080));
    this->board = sf::Sprite(tex);
    this->board.scale(width / 1920.0f, height / 1080.0f);
}

Game::~Game()
{
	delete this->window;
}

void Game::run() {
    while(this->window->isOpen()) {
        this->update();
        this->render();
    }
}

void Game::render() {
    this->window->clear(sf::Color::Black);
    this->window->draw(this->board);
    this->window->display();
}

void Game::update() {
    sf::Event event;
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            this->window->close();
    }
}