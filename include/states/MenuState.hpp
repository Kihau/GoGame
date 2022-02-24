#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "states/State.hpp"
#include "states/GameState.hpp"
#include "states/StatsState.hpp"
#include "states/SettingsState.hpp"
#include "Animation.hpp"

class MenuState : public State {
private:
	sf::Texture bg_tex;
	sf::Sprite background;
    sf::Font font;
    sf::Text title;

    // menu "buttons"
    std::vector<sf::Text> buttons;

    sf::Texture white_stone_tex;
	sf::Sprite white_stone;
	Animation white_anim;

    sf::Texture black_stone_tex;
    sf::Sprite black_stone;
	Animation black_anim;
    
public:
    MenuState(sf::RenderWindow* window);
    void draw();
    void update(const std::vector<sf::Event>&, sf::Time);
    //bool stateChange(std::stack<std::shared_ptr<State>>&);
};

#endif