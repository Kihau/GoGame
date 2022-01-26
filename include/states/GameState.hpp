#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"

#include "states/IState.hpp"

#include "Types.hpp"
#include "Board.hpp"
#include "gui/Button.hpp"

class GameState : public IState {
private:
    Button btn;
	std::unique_ptr<Board> board;

	sf::Texture bg_tex;
	sf::Sprite background;
	sf::Font font;

	std::vector<sf::Text> buttons;
	//sf::Text score_white_text;
	//sf::Text score_black_text;
	//sf::Text swap_state_text;
	//sf::Text current_turn_text;

	/* ADD:
		- Black and white score string
		- Current turn string
		- (is) Turn swapping on/off string
	*/
	
	f32 dt;

	sf::Texture wbag_tex;
	sf::Texture bbag_tex;
	sf::Sprite white_bag;
	sf::Sprite black_bag;

public:
    //GameState();
    GameState(sf::RenderWindow*);
    void draw();
    void update();
    bool stateChange(std::stack<std::shared_ptr<IState>>&);
};

#endif