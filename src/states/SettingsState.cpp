#include "states/SettingsState.hpp"

SettingsState::SettingsState(sf::RenderWindow* window) {
    this->window = window;

    this->bg_tex.loadFromFile("resources/textures/background.png");
    this->background = sf::Sprite(bg_tex);

    this->font.loadFromFile("resources/fonts/dpcomic.ttf");
    this->buttons = std::vector<sf::Text>(5);

    auto status = [](bool flag) {
        if (flag) 
            return std::string("enabled");
        
        return std::string("disabled");
    };

    this->buttons[0].setString("Show FPS: " + status(Settings::showFps));
    this->buttons[1].setString("Limit FPS: " + status(Settings::limitFps));
    this->buttons[2].setString("Max FPS: " + std::to_string(Settings::maxFps));
    this->buttons[3].setString("Console logging: " + status(Settings::enableLogging));
    this->buttons[4].setString("Sounds: " + status(Settings::enableSounds));

    for (auto i = 0; i < this->buttons.size(); i++) {
        buttons[i].setFont(this->font);
        buttons[i].setCharacterSize(150);
        float pos_x = (this->window->getView().getSize().x / 2.0) - (buttons[i].getGlobalBounds().width / 2.0);
        buttons[i].setPosition(sf::Vector2f(pos_x, 80.0f + 140.0f * i));
        buttons[i].setFillColor(sf::Color::White);
        buttons[i].setOutlineColor(sf::Color(71, 34, 0));
    }

    back_btn.setCharacterSize(100);
    back_btn.setString("BACK");
    back_btn.setFont(this->font);
    back_btn.setPosition(sf::Vector2f(1650.0f, 900.0f));
    back_btn.setFillColor(sf::Color::White);
    back_btn.setOutlineColor(sf::Color(71, 34, 0));
}

void SettingsState::draw() {
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

void SettingsState::update(const std::vector<sf::Event>& events, sf::Time) {
    for (auto& event : events) {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) 
                || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                this->pop = true;
            break;

        case sf::Event::MouseButtonPressed: {
            auto pos = sf::Mouse::getPosition(*window);
            auto map = this->window->mapPixelToCoords(pos);
            if (Settings::enableLogging) {
                std::cout << "Relative click - x: " << pos.x << " y: " << pos.y << "\n";
                std::cout << "Absolute click - x: " << map.x << " y: " << map.y << "\n\n";
            }

            int index = -1;
            for (auto i = 0; i < this->buttons.size(); i++) {
                auto b = this->buttons[i].getGlobalBounds();
                if (map.x >= b.left && map.x <= b.left + b.width
                    && map.y >= b.top && map.y <= b.top + b.height)
                    index = i;
            }

            auto status = [](bool flag) {
            if (flag) 
                return std::string("enabled");

            return std::string("disabled");
            };

            if (index == 0) {
                Settings::showFps = !Settings::showFps;
                this->buttons[0].setString("Show FPS: " + status(Settings::showFps));
            } else if (index == 1) {
                Settings::limitFps = !Settings::limitFps;
                this->buttons[1].setString("Limit FPS: " + status(Settings::limitFps));

                if (Settings::limitFps) 
                    this->window->setFramerateLimit(Settings::maxFps);
                else this->window->setFramerateLimit(0);
            } else if (index == 2 && Settings::limitFps) {
                Settings::maxFps = Settings::maxFps > 240 || Settings::maxFps <= 0 ? 15 : Settings::maxFps * 2;
                this->buttons[2].setString("Max FPS: " + std::to_string(Settings::maxFps));
                this->window->setFramerateLimit(Settings::maxFps);
            } else if (index == 3) {
                Settings::enableLogging = !Settings::enableLogging;
                this->buttons[3].setString("Console logging: " + status(Settings::enableLogging));
            } else if (index == 4) {
                Settings::enableSounds = !Settings::enableSounds;
                this->buttons[4].setString("Sounds: " + status(Settings::enableSounds));
            }

            auto b = this->back_btn.getGlobalBounds();
            if (map.x >= b.left && map.x <= b.left + b.width
                && map.y >= b.top && map.y <= b.top + b.height)
                this->pop = true;
            break;
        }
        }
    }
}