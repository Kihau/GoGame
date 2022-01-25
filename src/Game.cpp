#include "Game.hpp"

Game::Game()
{
    this->dt = 0.0f;

    this->window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(width, height), 
        "GoGame by Kihau"
    );
    this->window->setFramerateLimit(60);

    this->gameView = sf::View(sf::FloatRect(0, 0, 1920.0f, 1080.0f));
    this->window->setView(gameView);      

    this->bg_tex.loadFromFile("resources/textures/go.png");
    this->background = sf::Sprite(bg_tex);

    std::cout << window->getSize().x << " " << window->getSize().y;

}

Game::~Game() { }

void Game::run() {
    //this->window->setSize(sf::Vector2u(1280, 720));
    while(this->window->isOpen()) {
        this->update();
        this->render();
    }
}

void Game::render() {
    this->window->clear(sf::Color::Black);
    this->window->draw(this->background);
    this->window->draw(this->board);
    this->window->display();
}

void Game::update() {
    this->dispatchEvents();
}


// This could generate (or operate) on a event structure holding event data (InputManager or DispachedEvents)
void Game::dispatchEvents() {
    sf::Event event;
    while (this->window->pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::MouseButtonReleased: {
            auto pos = sf::Mouse::getPosition(*window);
            auto map = this->window->mapPixelToCoords(pos);
            std::cout << pos.x << " " << pos.y << "\n";
            std::cout << map.x << " " << map.y << "\n";
            std::cout << "\n";

            this->board.update(map, true);
            break;
        }

        case sf::Event::MouseMoved: {
            auto pos = sf::Mouse::getPosition(*window);
            auto map = this->window->mapPixelToCoords(pos);
            this->board.update(map, false);
            break;
        }

        case sf::Event::Resized:
            //this->targetView.setScale(this->width / 1920.0f, this->height / 1080.0f);
            break;
        }
    }
}

/// TODO: Create a logger class (implement ofstream operator?)
/// logger should output evert structure every 500ms
void Game::log() {

}