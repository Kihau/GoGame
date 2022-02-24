#include "states/GameState.hpp"

//GameState::GameState() {}
//GameState::~GameState() {}

GameState::GameState(sf::RenderWindow* window) {
    this->window = window;

    this->board = std::make_unique<Board>();

    this->dt = 0.0f;

    this->bg_tex.loadFromFile("resources/textures/background.png");
    this->background = sf::Sprite(bg_tex);

    std::cout << window->getSize().x << " " << window->getSize().y;

    this->font.loadFromFile("resources/fonts/dpcomic.ttf");

    this->bbag_tex.loadFromFile("resources/textures/black-bag.png");
    this->wbag_tex.loadFromFile("resources/textures/white-bag.png");

    this->white_bag.setTexture(this->wbag_tex);
    this->white_bag.setPosition(sf::Vector2f(1050, 320));
    this->white_bag.rotate(sf::degrees(-90.0f));
    this->white_bag.setColor(sf::Color(220, 220, 220));
    this->black_bag.setTexture(this->bbag_tex);
    this->black_bag.setPosition(sf::Vector2f(1050, 1030));
    this->black_bag.rotate(sf::degrees(-90.0f));
    this->black_bag.setColor(sf::Color(220, 220, 220));

    this->buttons = { 
        sf::Text("reset", this->font, 100),
        sf::Text("swap", this->font, 100),
        sf::Text("EXIT", this->font, 200),
        sf::Text("White score: 0", this->font, 80),
        sf::Text("Black score: 0", this->font, 80),
        sf::Text("Swap state: on", this->font, 80),
        sf::Text("Current turn:\n     white", this->font, 80),
        sf::Text("save", this->font, 100),
        sf::Text("load", this->font, 100),
    };

    for (auto& txt : this->buttons) {
        txt.setFillColor(sf::Color::White);
        txt.setOutlineColor(sf::Color(71, 34, 0));
    }

    this->buttons[0].setPosition(sf::Vector2f(1100, 310));
    this->buttons[1].setPosition(sf::Vector2f(1100, 420));

    this->buttons[2].setPosition(sf::Vector2f(1450, 50));

    this->buttons[3].setPosition(sf::Vector2f(1370, 340));
    this->buttons[4].setPosition(sf::Vector2f(1370, 450));
    this->buttons[5].setPosition(sf::Vector2f(1370, 620));
    this->buttons[6].setPosition(sf::Vector2f(1370, 800));

    this->buttons[7].setPosition(sf::Vector2f(1100, 530));
    this->buttons[8].setPosition(sf::Vector2f(1100, 640));
}

void GameState::draw() {
    //sf::Text text;
    //text.setFont(this->font);
    //text.setPosition(100.0f, 100.0f);
    //text.setCharacterSize(150);
    //text.setString("A Very Fancy Text");
    //text.setColor(sf::Color::Black);

    this->window->draw(this->background);
    this->window->draw(*this->board);

    this->window->draw(this->white_bag);
    this->window->draw(this->black_bag);

    for (auto& btn : this->buttons) {
        auto og = btn.getPosition();

        btn.setPosition(sf::Vector2f(og.x - 7, og.y - 7));
        btn.setFillColor(sf::Color(71, 34, 0));
        btn.setOutlineThickness(5.0f);
        this->window->draw(btn);

        btn.setPosition(og);
        btn.setOutlineThickness(0.0f);
        btn.setFillColor(sf::Color::White);
        this->window->draw(btn);
    }

    //this->window->draw(text);
    this->window->draw(this->btn);
}

void GameState::update(const std::vector<sf::Event>& events, sf::Time deltaTime) {
    for (auto& event : events) {
        switch (event.type)
        {
        case sf::Event::MouseButtonReleased: {
            auto pos = sf::Mouse::getPosition(*window);
            auto map = this->window->mapPixelToCoords(pos);
            this->board->update(map, true);
            break;
        }

        case sf::Event::MouseButtonPressed: {
            auto pos = sf::Mouse::getPosition(*window);
            auto map = this->window->mapPixelToCoords(pos);

            // Button - bag white
            auto wb = this->white_bag.getGlobalBounds();
            if (map.x >= wb.left && map.x <= wb.left + wb.width
                && map.y >= wb.top && map.y <= wb.top + wb.height) {
                    this->board->setTurn(2);
            }

            // Button - bag black
            auto bb = this->black_bag.getGlobalBounds();
            if (map.x >= bb.left && map.x <= bb.left + bb.width
                && map.y >= bb.top && map.y <= bb.top + bb.height) {
                    this->board->setTurn(1);
            }

            // Dispatching text "buttons"
            int index = -1;
            for (auto i = 0; i < this->buttons.size(); i++) {
                auto b = this->buttons[i].getGlobalBounds();
                if (map.x >= b.left && map.x <= b.left + b.width
                    && map.y >= b.top && map.y <= b.top + b.height)
                    index = i;
            }

            // Invoking event
            if (index == 0) this->board = std::make_unique<Board>();
            else if (index == 1) this->board->changeSwap();
            else if (index == 2) this->pop = true;
            else if (index == 7) {
                std::ofstream file("boardsave.dat", std::ios::binary);
                file << (*board);
                file.close();
            }
            else if (index == 8) {
                std::ifstream file("boardsave.dat", std::ios::binary);
                if (file) 
                    file >> (*board);
                file.close();
            }
        }

        case sf::Event::MouseMoved: {
            auto pos = sf::Mouse::getPosition(*window);
            auto map = this->window->mapPixelToCoords(pos);
            this->board->update(map, false);
            break;
        }

        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
                || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                this->pop = true;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) 
                this->push = std::make_shared<GameState>(this->window);
            break;

        case sf::Event::Resized:
            //this->targetView.setScale(this->width / 1920.0f, this->height / 1080.0f);
            break;
        }
    }

    std::string s = "White score: " + std::to_string(this->board->getScoreWhite());
    this->buttons[3].setString(s);
    s = "Black score: " + std::to_string(this->board->getScoreBlack());
    this->buttons[4].setString(s);

    if (this->board->getSwapState()) 
        s = "Swap turn: on";
    else s = "Swap turn: off";

    this->buttons[5].setString(s);

    s = "Current turn:\n     " + this->board->getTurnString();
    this->buttons[6].setString(s);
}