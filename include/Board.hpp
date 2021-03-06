#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <algorithm>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Types.hpp"
#include "Stone.hpp"
#include "StoneGroup.hpp"
#include "Settings.hpp"

class Board : public sf::Drawable {
private:
    f32 offset = 0;
    const size_t size = 19;
    std::vector<Stone> stones;
    sf::Texture texture;
    sf::Sprite sprite;

    std::vector<StoneGroup> groups;

    sf::Texture stone_texture;
    sf::Sprite stone_sprite;
    const f32 stone_scale = 0.07f;

    // CHANGE IT TO ENUM
    // 0 - none
    // 1 - black
    // 2 - white

    i32 score_white = 0;
    i32 score_black = 0;

    bool swap_turns = true;
    i32 turn = 1;
    sf::Vector2i last_highlight;
    sf::Vector2i last_move;
    sf::CircleShape red_dot;

    void makeMove(sf::Vector2f pos);
    void setHighlight(sf::Vector2f pos);
    void clearHighlight();

    void groupAdd(sf::Vector2i, i32 color);
    void groupErase(sf::Vector2i);

    sf::Vector2i getPosFromCoords(sf::Vector2f);
    sf::Vector2i getPosFromIndex(i32);
    i32 getIndexFromPos(sf::Vector2i);

    sf::SoundBuffer buffer;
    sf::Sound stone_sound;

public:
    Board();

    /// TODO: this vvv
    Board(size_t size);
    ~Board();
    void draw(sf::RenderTarget&, const sf::RenderStates&) const;
    void update(sf::Vector2f pos, bool);
    void setTurn(i32);
    std::string getTurnString();
    void changeSwap();
    bool getSwapState();
    i32 getScoreWhite();
    i32 getScoreBlack();

    friend std::ostream &operator<<(std::ostream&, const Board&);
    friend std::istream &operator>>(std::istream&, Board&);
    void serialize(std::ostream&) const;
    void deserialize(std::istream&);

    void saveImage() const;
};

#endif