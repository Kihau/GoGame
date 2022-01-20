#include "Game.hpp"

Game::Game()
{
    this->dt = 0.0f;

    // this->window = new sf::RenderWindow(sf::VideoMode(width, height), "GoGame by Kihau");
    this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "GoGame by Kihau");

    this->window->setFramerateLimit(60);

    // testing
    this->target.create(1920, 1080);

    this->tex.loadFromFile("resources/textures/go.png");
    this->tex2.loadFromFile("resources/textures/board.png");
    this->tex3.loadFromFile("resources/textures/white.png");

    this->bg = sf::Sprite(tex);
    this->target.draw(bg);

    this->board = sf::Sprite(tex2);
    this->board.scale(0.5f, 0.5f);
    this->board.setPosition(40.0f, 40.0f);
    this->target.draw(board);

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
    sf::Sprite to_draw(this->target.getTexture());
    to_draw.setScale(this->width / 1920.0f, this->height / 1080.0f);

    this->window->draw(to_draw);
    //this->window->draw(this->bg);
    //this->window->draw(this->board);
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            auto sprite = sf::Sprite(tex3);
            switch (this->dots[i][j])
            {
            case 1: sprite.setColor(sf::Color::White); break;
            case 2: sprite.setColor(sf::Color::Black); break;
            default: sprite.setColor(sf::Color::Transparent); break;
            }
            sprite.scale(width / 1920.0f * 0.06f, height / 1080.0f * 0.06f);
            sprite.setPosition(34.7f + i * 34.7f, 34.7f + j * 34.7f);
            this->window->draw(sprite);
        }
    }
    this->window->display();
}

void Game::update() {
    sf::Event event;
    while (this->window->pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::MouseButtonPressed:
            auto pos = sf::Mouse::getPosition(*window);
            if (pos.x > 46 && pos.x < 692 && pos.y > 26 && pos.y < 692) {
                int x = (pos.x - 26) / 36;
                int y = (pos.y - 26) / 36;

                if (this->dots[x][y] == 0) {
                    if (this->player)
                        this->dots[x][y] = 1;
                    else this->dots[x][y] = 2;

                    this->player = !this->player;
                }

            }
            std::cout << pos.x << " " << pos.y << "\n\n";
            break;
    
        }
    }
}

void Game::log() {

}