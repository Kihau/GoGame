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
    this->white_bag.setPosition(1050, 350);
    this->white_bag.rotate(-90.0f);
    this->white_bag.setColor(sf::Color(220, 220, 220));
    this->black_bag.setTexture(this->bbag_tex);
    this->black_bag.setPosition(1050, 1000);
    this->black_bag.rotate(-90.0f);
    this->black_bag.setColor(sf::Color(220, 220, 220));

    this->buttons = { 
        sf::Text("reset", this->font, 100),
        sf::Text("swap", this->font, 100),
        sf::Text("EXIT", this->font, 200),
        sf::Text("White score: 0", this->font, 80),
        sf::Text("Black score: 0", this->font, 80),
        sf::Text("Swap state: on", this->font, 80),
        sf::Text("Current turn:\n     white", this->font, 80),
    };

    for (auto& txt : this->buttons) {
        txt.setFillColor(sf::Color::White);
        txt.setOutlineColor(sf::Color(71, 34, 0));
    }

    this->buttons[0].setPosition(1100, 400);
    this->buttons[1].setPosition(1100, 550);
    this->buttons[2].setPosition(1450, 50);

    this->buttons[3].setPosition(1370, 340);
    this->buttons[4].setPosition(1370, 450);
    this->buttons[5].setPosition(1370, 620);
    this->buttons[6].setPosition(1370, 800);

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

void GameState::update() {
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

            this->board->update(map, true);
            break;
        }

        case sf::Event::MouseButtonPressed: {
            auto pos = sf::Mouse::getPosition(*window);
            auto map = this->window->mapPixelToCoords(pos);

            auto wb = this->white_bag.getGlobalBounds();
            std::cout << wb.left << " " << wb.width << " " << wb.left + wb.width << "\n";            
            if (map.x >= wb.left && map.x <= wb.left + wb.width
                && map.y >= wb.top && map.y <= wb.top + wb.height) {
                    this->board->setTurn(2);
                    std::cout << "pressed white\n";
            }

            auto bb = this->black_bag.getGlobalBounds();
            if (map.x >= bb.left && map.x <= bb.left + bb.width
                && map.y >= bb.top && map.y <= bb.top + bb.height) {
                    this->board->setTurn(1);
                    std::cout << "pressed black\n";
            }

            int index = -1;
            for (auto i = 0; i < this->buttons.size(); i++) {
                auto b = this->buttons[i].getGlobalBounds();
                if (map.x >= b.left && map.x <= b.left + b.width
                    && map.y >= b.top && map.y <= b.top + b.height)
                    index = i;
            }

            if (index == 0) this->board = std::make_unique<Board>();
            else if (index == 1) this->board->changeSwap();
            else if (index == 2) this->pop = true;
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
                this->push = true;
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

bool GameState::stateChange(std::stack<std::shared_ptr<State>>& states) {
    if (this->push) {
        this->push = false;
        auto state = std::make_shared<GameState>(this->window);
        states.push(state);
        return true;
    } 

    if (this->pop) {
        this->pop = false;
        states.pop();
        return true;
    } 

    return false;
}