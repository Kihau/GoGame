#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "states/State.hpp"
#include "states/GameState.hpp"
#include "Animation.hpp"

class MenuState : public State {
private:
	sf::Texture bg_tex;
	sf::Sprite background;
    sf::Font font;
    sf::Text title;
    // sf::Text start;
    // sf::Text about;z
    // sf::Text options;
    // sf::Text exit;

    // menu "buttons"
    std::vector<sf::Text> buttons;

    sf::Texture white_stone_tex;
	sf::Sprite white_stone;
	Animation anim;
    
public:
    MenuState(sf::RenderWindow* window);
    void draw();
    void update(const std::vector<sf::Event>&, sf::Time);
    bool stateChange(std::stack<std::shared_ptr<State>>&);
};

#endif