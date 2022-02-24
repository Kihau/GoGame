#include "Game.hpp"

Game::Game() {
    this->window = new sf::RenderWindow(
        sf::VideoMode(width, height), 
        "GoGame by Kihau"
    );

    if (Settings::limitFps)
        this->window->setFramerateLimit(Settings::maxFps);

    this->gameView = sf::View(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1920.0f, 1080.0f)));
    this->window->setView(gameView);   

    auto init_state = std::make_shared<MenuState>(this->window);
    this->states.push(init_state);

    this->fps_font.loadFromFile("resources/fonts/anton.ttf");
    this->fps.setFont(this->fps_font);
    this->fps.setPosition(sf::Vector2f(1700.0f, 50.0f));
    this->fps.setCharacterSize(80);
    this->fps.setFillColor(sf::Color(140, 10, 0));
}

Game::~Game() { 
    delete this->window;
}

void Game::run() {
    while(this->window->isOpen() && !this->states.empty()) {
        auto currTime = this->gameClock.getElapsedTime();

        this->dispatchEvents();

        if (Settings::enableLogging)
            this->logEvents();

        this->states.top()->update(this->events, this->deltaTime);

        this->events.clear();
        if (this->states.top()->stateChange(this->states))
            continue;

        this->window->clear(sf::Color::Black);

        this->states.top()->draw();

        if (Settings::showFps) {
            std::stringstream stream;
            stream << std::setprecision(4) << 1000000 / (float)this->deltaTime.asMicroseconds();
            this->fps.setString(stream.str());
            this->window->draw(this->fps);
        }

        this->window->display();

        this->deltaTime = currTime - this->prevTime;
        this->totalTime += this->deltaTime;
        this->logTime = this->logTime + this->deltaTime;

        Stats::ingameTime = this->totalTime.asMicroseconds();
        Stats::totalTime += this->deltaTime.asMicroseconds();

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
            case sf::Event::MouseButtonPressed:
                Stats::mouseClicks++;
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
        std::cout << "Delta: " << this->deltaTime.asMicroseconds() << "μs\n";
        std::cout << "Total ingame time: " << this->totalTime.asSeconds() << "s\n";
        std::cout << std::endl;

        this->logTime = sf::Time();
    }
}