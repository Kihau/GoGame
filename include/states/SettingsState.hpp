#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include <iostream>

#include "SFML/Window.hpp"

#include "states/State.hpp"
#include "Settings.hpp"

class SettingsState : public State {
private:
    sf::Texture bg_tex;
	sf::Sprite background;

    sf::Font font;
    std::vector<sf::Text> buttons;
    sf::Text back_btn;

    void setButton(const std::string&);
    
public:
    SettingsState(sf::RenderWindow* window);
    void draw();
    void update(const std::vector<sf::Event>&, sf::Time);
};

#endif