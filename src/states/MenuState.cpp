#include "states/MenuState.hpp"

MenuState::MenuState(sf::RenderWindow* window) {
    this->window = window;

    this->bg_tex.loadFromFile("resources/textures/background.png");
    this->background = sf::Sprite(bg_tex);

    this->font.loadFromFile("resources/fonts/dpcomic.ttf");
    this->title = sf::Text("GoGame", this->font, 300);
    this->title.setPosition(sf::Vector2f(500.0f, 0.0f));
    this->title.setFillColor(sf::Color::White);
    this->title.setOutlineColor(sf::Color(71, 34, 0));

    std::vector<std::string> strings {
        "start",
        "options",
        "about",
        "exit",
    };

    for (auto i = 0; i < strings.size(); i++) {
        auto txt = sf::Text(strings[i], this->font, 150);
        txt.setPosition(770.0f, 350.0f + 140.0f * i);
        txt.setFillColor(sf::Color::White);
        txt.setOutlineColor(sf::Color(71, 34, 0));
        this->buttons.push_back(txt);
    }
}


void MenuState::draw() {
    this->window->draw(this->background);

    auto og = this->title.getPosition();

    this->title.setPosition(sf::Vector2f(og.x - 10, og.y - 10));
    this->title.setFillColor(sf::Color(71, 34, 0));
    this->title.setOutlineThickness(7.0f);
    this->window->draw(title);

    this->title.setPosition(og);
    this->title.setOutlineThickness(0.0f);
    this->title.setFillColor(sf::Color::White);
    this->window->draw(title);

    for (auto& btn : this->buttons) {

        og = btn.getPosition();

        btn.setPosition(sf::Vector2f(og.x - 7, og.y - 7));
        btn.setFillColor(sf::Color(71, 34, 0));
        btn.setOutlineThickness(5.0f);
        this->window->draw(btn);

        btn.setPosition(og);
        btn.setOutlineThickness(0.0f);
        btn.setFillColor(sf::Color::White);
        this->window->draw(btn);
    }
}

void MenuState::update() {
        sf::Event event;
    while (this->window->pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::MouseButtonReleased: {
            auto pos = sf::Mouse::getPosition(*window);
            std::cout << "Relative click - x: " << pos.x << " y: " << pos.y << "\n";
            auto map = this->window->mapPixelToCoords(pos);
            std::cout << "Absolute click - x: " << map.x << " y: " << map.y << "\n\n";

            int index = -1;
            for (auto i = 0; i < this->buttons.size(); i++) {
                auto b = this->buttons[i].getGlobalBounds();
                if (map.x >= b.left && map.x <= b.left + b.width
                    && map.y >= b.top && map.y <= b.top + b.height)
                    index = i;
            }

            if (index == 0) this->push = true;
            else if (index == 3) this->pop = true;

            break;
        }

        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) 
                || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                this->pop = true;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) 
                this->push = true;
            break;

        }

    }
}

bool MenuState::stateChange(std::stack<std::shared_ptr<State>>& states) {
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
