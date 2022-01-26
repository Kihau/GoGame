#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "states/IState.hpp"
#include "states/GameState.hpp"

class MenuState : public IState {
private:
	sf::Texture bg_tex;
	sf::Sprite background;
    sf::Font font;
    sf::Text title;
    // sf::Text start;
    // sf::Text about;
    // sf::Text options;
    // sf::Text exit;

    // menu "buttons"
    std::vector<sf::Text> buttons;
    
public:
    MenuState(sf::RenderWindow* window);
    void draw();
    void update();
    bool stateChange(std::stack<std::shared_ptr<IState>>&);
};

#endif