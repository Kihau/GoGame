#include "Game.hpp"

Game::Game() {
    this->window = new sf::RenderWindow(
        sf::VideoMode(width, height), 
        "GoGame by Kihau"
    );
    this->window->setFramerateLimit(60);

    this->gameView = sf::View(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1920.0f, 1080.0f)));
    this->window->setView(gameView);   

    auto init_state = std::make_shared<MenuState>(this->window);
    this->states.push(init_state);

    if (!this->something.loadFromFile("resources/textures/white-sheet.png"))
        std::cout << "Failed to load";
        
    this->idk.setTexture(this->something);
    this->anim = Animation(&idk);
    this->idk.setPosition(sf::Vector2f(200, 450));
    this->idk.setScale(sf::Vector2f(1.5f, 1.5f));

    this->anim.addFrame({ sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(240, 240)), 0.08 });
    this->anim.addFrame({ sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(240, 240)), 0.08 });
    for (int  i = 0; i < 8; i++)
        this->anim.addFrame({ sf::IntRect(sf::Vector2i(i*240, 0), sf::Vector2i(240, 240)), 0.08 });
}

Game::~Game() { 
    delete this->window;
}

void Game::run() {
    while(this->window->isOpen() && !this->states.empty()) {
        auto currTime = this->gameClock.getElapsedTime();

        this->dispatchEvents();
        this->logEvents();

        this->states.top()->update(this->events);

        this->events.clear();
        if (this->states.top()->stateChange(this->states))
            continue;

        this->anim.update(this->deltaTime.asSeconds());

        this->window->clear(sf::Color::Black);

        this->states.top()->draw();
        //this->window->draw(this->idk);
        this->window->display();

        this->deltaTime = currTime - this->prevTime;
        this->logTime = this->logTime + this->deltaTime;

        this->prevTime = currTime;
    }
}

void Game::dispatchEvents() {
    sf::Event event;
    while (this->window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
        }
        this->events.push_back(event);
    }
}

void Game::logEvents() {
    if (this->logTime.asMilliseconds() > this->log_delay) {
        for (auto e : this->events) {
            switch (e.type) {
            case sf::Event::MouseMoved:
                break;
            }
        }
        
        auto pos = sf::Mouse::getPosition();
        std::cout << "Mouse pos x: " << pos.x << " y: " << pos.y << "\n";
        std::cout << "Delta: " << this->deltaTime.asMicroseconds() << "ms\n";

        this->logTime = sf::Time();
    }
}