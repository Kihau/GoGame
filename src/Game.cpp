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

    this->font.loadFromFile("resources/fonts/dpcomic.ttf");


    this->bbag_tex.loadFromFile("resources/textures/black-bag.png");
    this->wbag_tex.loadFromFile("resources/textures/white-bag.png");

    this->white_bag.setTexture(this->wbag_tex);
    this->white_bag.setPosition(1050, 350);
    this->white_bag.rotate(-90.0f);
    this->white_bag.setColor(sf::Color(220, 220, 220));
    this->black_bag.setTexture(this->bbag_tex);
    this->black_bag.setPosition(1050, 1000);
    this->black_bag.rotate(-90.0f);
    this->black_bag.setColor(sf::Color(220, 220, 220));

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
    //sf::Text text;
    //text.setFont(this->font);
    //text.setPosition(100.0f, 100.0f);
    //text.setCharacterSize(150);
    //text.setString("A Very Fancy Text");
    //text.setColor(sf::Color::Black);

    this->window->clear(sf::Color::Black);

    this->window->draw(this->background);
    this->window->draw(this->board);

    this->window->draw(this->white_bag);
    this->window->draw(this->black_bag);

    //this->window->draw(text);
    this->window->draw(this->btn);

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

        case sf::Event::MouseButtonPressed: {
            auto pos = sf::Mouse::getPosition(*window);
            auto map = this->window->mapPixelToCoords(pos);

            auto wb = this->white_bag.getGlobalBounds();
            std::cout << wb.left << " " << wb.width << " " << wb.left + wb.width << "\n";            
            if (map.x >= wb.left && map.x <= wb.left + wb.width
                && map.y >= wb.top && map.y <= wb.top + wb.height) {
                    this->board.setTurn(2);
                    std::cout << "pressed white\n";
            }

            auto bb = this->black_bag.getGlobalBounds();
            if (map.x >= bb.left && map.x <= bb.left + bb.width
                && map.y >= bb.top && map.y <= bb.top + bb.height) {
                    this->board.setTurn(1);
                    std::cout << "pressed\n";
            }
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