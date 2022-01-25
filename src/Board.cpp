#include "Board.hpp"

// custom map generation

// allow to set custom board size:
//      generate texture by looping tiles sprite
//      draw generated texture on top of a yellowish box
//      make generated texture a drawing sprite
// generate board sprites (from 10 to 30 ???)
Board::Board() {

    // generate board sprite
    /* CODE HERE */

    this->last_highlight = sf::Vector2i(-1, -1);

    /// INITIALIZE BOARD

    this->texture.loadFromFile("resources/textures/board.png");
    this->sprite.setTexture(this->texture);

    /// TODO: fix to not be hardcoded
    this->sprite.scale(0.48f, 0.48f);
    offset = (1012 - this->sprite.getGlobalBounds().width) / 2 + 34;
    this->sprite.setPosition(offset, offset);

    
    /// INITIALIZE STONES

    this->stone_texture.loadFromFile("resources/textures/white.png");
    this->stone_sprite.setScale(this->stone_scale, this->stone_scale);

    stone_sprite.setTexture(this->stone_texture);
    std::cout << "\n" << this->stone_sprite.getGlobalBounds().width << "\n";
    stone_sprite.setColor(sf::Color::Transparent);

    // copy sprite to a Stone struct
    Stone temp_stone = { 0, stone_sprite };
    // populate vector with copies of Stone
    this->stones = std::vector<Stone>(size * size, temp_stone);

    this->last_move = sf::Vector2i(-1, -1);
    this->red_dot.setFillColor(sf::Color::Red);
    this->red_dot.setRadius(this->stone_sprite.getGlobalBounds().width / 6);
}

Board::~Board() {}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // draw board
    target.draw(this->sprite, states);

    // draw all stones
    for (auto& stone : this->stones) 
        target.draw(stone.sprite);

    // draw stone hightlight
    if (this->last_move.x != -1) 
        target.draw(this->red_dot);

    // draw stone hightlight
    if (this->last_highlight.x != -1) 
        target.draw(this->stone_sprite);
}

// void old_dummy_cringe_function() {
//     bool added = false;
//     std::vector<size_t> added_groups;
//     for (auto i = 0; i < this->groups.size(); i++) {
//         if (this->groups[i].canAdd(sf::Vector2i(x, y), this->turn)) {
//             this->groups[i].addStone(sf::Vector2i(x, y));
//             added_groups.push_back(i);
//             added = true;
//         }
            
//     }

//     if (added) {
//         StoneGroup combined_group(this->turn);
//         for (auto i : added_groups) {
//             combined_group.combineGroups(groups[i]);
//         }

//         std::sort(added_groups.begin(), added_groups.end(), std::greater<size_t>());
//         for (auto i : added_groups) {
//             this->groups[i] = this->groups.back();
//             this->groups.pop_back();
//         }

//         this->groups.push_back(combined_group);
//     } else this->groups.push_back(StoneGroup(sf::Vector2i(x, y), this->turn));

        // std::vector<size_t> adjacent_groups;
        // for (auto i = 0; i < groups.size(); i++) {
        //     if (groups[i].isAdjacent(sf::Vector2i(x, y))) {   
        //         adjacent_groups.push_back(i);
        //     }        
        // }

        // std::vector<size_t> to_erase;

        // std::sort(
        //     adjacent_groups.begin(), 
        //     adjacent_groups.end(), 
        //     std::greater<size_t>()
        // );

        // for (auto i : adjacent_groups) {
        //     if (this->groups[i].checkLibreties(this->stones, this->size) == 0) {
        //         this->groups[i].removeStones(this->stones, this->size);

        //         this->groups[i] = this->groups.back();
        //         this->groups.pop_back();
        //     }
        // }

        /// OLDER OLD

        // std::vector<size_t> to_erase;
        // for (auto i = 0; i < groups.size(); i++) {
        //     if (groups[i].checkLibreties(this->stones, this->size) == 0)
        //         to_erase.push_back(i);
        // }

        // std::sort(to_erase.begin(), to_erase.end(), std::greater<size_t>());
        // for (auto i : to_erase) {
        //     groups[i].removeStones(this->stones, this->size);

        //     this->groups[i] = this->groups.back();
        //     this->groups.pop_back();
        // }
// }


/// TODO: change: tile size and position of starting tile are hardcoded
void Board::makeMove(sf::Vector2f pos) {
    i32 unchecked_x = (pos.x - offset) / 50;
    i32 x = unchecked_x >= this->size ? this->size - 1 : unchecked_x;
    i32 unchecked_y = (pos.y - offset) / 50;
    i32 y = unchecked_y >= this->size ? this->size - 1 : unchecked_y;
    auto& stone = this->stones[x + this->size * y];

    // start - 60
    // first line - 90 
    // tile size - 50
    if (stone.turn == 0) {
        stone.turn = this->turn;
        auto stone_offset = 90 - this->stone_sprite.getGlobalBounds().width / 2;
        stone.sprite.setPosition(x * 50 + stone_offset, y * 50 + stone_offset);

        this->last_move = sf::Vector2i(x, y);
        auto dot_offset = 90 - this->red_dot.getGlobalBounds().width / 2;
        this->red_dot.setPosition(x * 50 + dot_offset, y * 50 + dot_offset);

        //////////////////////////////////////////////////////
        /// Group adding login - move somewhere else /////////
        bool added = false;
        std::vector<size_t> added_groups;
        for (auto i = 0; i < this->groups.size(); i++) {
            if (this->groups[i].canAdd(sf::Vector2i(x, y), this->turn)) {
                this->groups[i].addStone(sf::Vector2i(x, y));
                added_groups.push_back(i);
                added = true;
            }

        }

        if (added) {
            StoneGroup combined_group(this->turn);
            for (auto i : added_groups) {
                combined_group.combineGroups(groups[i]);
            }

            std::sort(added_groups.begin(), added_groups.end(), std::greater<size_t>());
            for (auto i : added_groups) {
                this->groups[i] = this->groups.back();
                this->groups.pop_back();
            }

            this->groups.push_back(combined_group);
        } else this->groups.push_back(StoneGroup(sf::Vector2i(x, y), this->turn));
        //////////////////////////////////////////////////////


        if (this->turn == 1) {
            this->turn = 2;
            stone.sprite.setColor(sf::Color::Black);
        } else {
            this->turn = 1;
            stone.sprite.setColor(sf::Color::White);
        }

        //////////////////////////////////////////////////////
        /// Librety checking logic ///////////////////////////
        std::vector<size_t> adjacent_groups;
        for (auto i = 0; i < groups.size(); i++) {
            if (groups[i].isAdjacent(sf::Vector2i(x, y))) {   
                adjacent_groups.push_back(i);
            }        
        }

        std::vector<size_t> to_erase;

        std::sort(
            adjacent_groups.begin(), 
            adjacent_groups.end(), 
            std::greater<size_t>()
        );

        for (auto i : adjacent_groups) {
            if (this->groups[i].checkLibreties(this->stones, this->size) == 0) {
                this->groups[i].removeStones(this->stones, this->size);

                this->groups[i] = this->groups.back();
                this->groups.pop_back();
            }
        }
        //////////////////////////////////////////////////////
    }

    std::cout << "click indexes: " << x << " " << y << "\n";
}

void Board::setHighlight(sf::Vector2f pos) {
    i32 unchecked_x = (pos.x - offset) / 50;
    i32 x = unchecked_x >= this->size ? this->size - 1 : unchecked_x;
    i32 unchecked_y = (pos.y - offset) / 50;
    i32 y = unchecked_y >= this->size ? this->size - 1 : unchecked_y;

    this->last_highlight.x = x;
    this->last_highlight.y = y;   

    auto stone_offset = 90 - this->stone_sprite.getGlobalBounds().width / 2;
    this->stone_sprite.setPosition(x * 50 + stone_offset, y * 50 + stone_offset);
    if (this->stones[x + this->size * y].turn != 0)
        this->stone_sprite.setColor(sf::Color(255, 0, 0, 80));
    else if (this->turn == 1)
        this->stone_sprite.setColor(sf::Color(0, 0, 0, 180));
    else this->stone_sprite.setColor(sf::Color(255, 255, 255, 180));
}

void Board::clearHighlight() {
    this->last_highlight.x = -1;
    this->last_highlight.y = -1;
    this->stone_sprite.setColor(sf::Color::Transparent);
}

void Board::update(sf::Vector2f pos, bool clicked) {
    auto sx = this->sprite.getPosition().x;
    auto sy = this->sprite.getPosition().y;
    auto widt = this->sprite.getGlobalBounds().width;
    auto high = this->sprite.getGlobalBounds().height;

    if (pos.x > sx && pos.x - sx < widt && pos.y > sy && pos.y - sy < high) {    
        if (clicked) 
            this->makeMove(pos);
        this->setHighlight(pos);
    } else this->clearHighlight();

    // Mechanics here - roll the logic
}