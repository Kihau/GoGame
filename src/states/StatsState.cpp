#include "states/StatsState.hpp"

StatsState::StatsState(sf::RenderWindow* window) {
    this->window = window;

    this->bg_tex.loadFromFile("resources/textures/background.png");
    this->background = sf::Sprite(bg_tex);

    this->font.loadFromFile("resources/fonts/dpcomic.ttf");
    
    std::vector<std::string> strings {
        "Total in-game time:",
        std::to_string(Stats::totalTime / 1000000) + " seconds",
        "Current in-game time:",
        std::to_string(Stats::ingameTime / 1000000) + " seconds",
        "Total mouse clicks: ",
        std::to_string(Stats::mouseClicks) + " clicks",
    };

    for (auto i = 0; i < strings.size(); i++) {
        auto txt = sf::Text(strings[i], this->font, 150);
        float pos_x = (this->window->getView().getSize().x / 2.0) - (txt.getGlobalBounds().width / 2.0);
        txt.setPosition(sf::Vector2f(pos_x, 80.0f + 140.0f * i));
        txt.setFillColor(sf::Color::White);
        txt.setOutlineColor(sf::Color(71, 34, 0));
        this->buttons.push_back(txt);
    }

    back_btn.setCharacterSize(100);
    back_btn.setString("BACK");
    back_btn.setFont(this->font);
    back_btn.setPosition(sf::Vector2f(1650.0f, 900.0f));
    back_btn.setFillColor(sf::Color::White);
    back_btn.setOutlineColor(sf::Color(71, 34, 0));
}

void StatsState::draw() {
    this->window->draw(this->background);

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

    this->buttons[1].setString(std::to_string(Stats::totalTime / 1000000) + " seconds");
    this->buttons[3].setString(std::to_string(Stats::ingameTime / 1000000) + " seconds");
    this->buttons[5].setString(std::to_string(Stats::mouseClicks) + " clicks");

    auto og = back_btn.getPosition();
    back_btn.setPosition(sf::Vector2f(og.x - 7, og.y - 7));
    back_btn.setFillColor(sf::Color(71, 34, 0));
    back_btn.setOutlineThickness(5.0f);
    this->window->draw(back_btn);

    back_btn.setPosition(og);
    back_btn.setOutlineThickness(0.0f);
    back_btn.setFillColor(sf::Color::White);
    this->window->draw(back_btn);
}

void StatsState::update(const std::vector<sf::Event>& events, sf::Time) {
    for (auto& event : events) {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) 
                || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                this->pop = true;
            break;

        case sf::Event::MouseButtonPressed: 
            auto b = this->back_btn.getGlobalBounds();
            auto pos = sf::Mouse::getPosition(*window);
            auto map = this->window->mapPixelToCoords(pos);
            if (map.x >= b.left && map.x <= b.left + b.width
                && map.y >= b.top && map.y <= b.top + b.height)
                this->pop = true;
            break;
        }
    }
}