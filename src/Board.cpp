#include "Board.hpp"

// custom map generation

// allow to set custom board size:
//      generate texture by looping tiles sprite
//      draw generated texture on top of a yellowish box
//      make generated texture a drawing sprite
// generate board sprites (from 5 to 30 ???)
Board::Board() {

    // generate board sprite
    /* CODE HERE */

    auto r = 0xfb;
    auto g = 0xbe;
    auto b = 0x82;

    this->last_highlight = sf::Vector2i(-1, -1);

    /// INITIALIZE BOARD

    this->texture.loadFromFile("resources/textures/board-pattern.png");
    this->sprite.setTexture(this->texture);
    //this->sprite.setColor(sf::Color(251, 190, 130));
    //this->sprite.setColor(sf::Color(255, 255, 255));

    /// TODO: fix to not be hardcoded
    this->sprite.scale(sf::Vector2f(0.48f, 0.48f));
    offset = (1012 - this->sprite.getGlobalBounds().width) / 2 + 34;
    this->sprite.setPosition(sf::Vector2f(offset, offset));

    
    /// INITIALIZE STONES

    this->stone_texture.loadFromFile("resources/textures/white.png");
    this->stone_sprite.setScale(sf::Vector2f(this->stone_scale, this->stone_scale));

    stone_sprite.setTexture(this->stone_texture);
    //std::cout << "\n" << this->stone_sprite.getGlobalBounds().width << "\n";
    stone_sprite.setColor(sf::Color::Transparent);

    // copy sprite to a Stone struct
    Stone temp_stone = { 0, stone_sprite };
    // populate vector with copies of Stone
    this->stones = std::vector<Stone>(size * size, temp_stone);
    for (auto i = 0; i < this->stones.size(); i++) {
        auto stone_offset = 90 - this->stone_sprite.getGlobalBounds().width / 2;
        auto y = i / this->size * 50 + stone_offset;
        auto x = (i - ((i / this->size) * this->size)) * 50 + stone_offset;
        this->stones[i].sprite.setPosition(sf::Vector2f(x, y));
    }

    this->last_move = sf::Vector2i(-1, -1);
    this->red_dot.setFillColor(sf::Color::Red);
    this->red_dot.setRadius(this->stone_sprite.getGlobalBounds().width / 6);

    this->buffer.loadFromFile("resources/audio/stone.mp3");
    this->stone_sound.setBuffer(this->buffer);
}

Board::~Board() {}

void Board::setTurn(int turn) {
    this->turn = turn;
}

std::string Board::getTurnString() {
    if (this->turn == 1)
        return "Black";
    else return "White";
}

void Board::changeSwap() {
    this->swap_turns = !this->swap_turns;
}

bool Board::getSwapState() {
    return this->swap_turns;
}

i32 Board::getScoreWhite() {
    return this->score_white;
}


i32 Board::getScoreBlack() {
    return this->score_black;
}


void Board::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    // draw board
    target.draw(this->sprite, states);

    // draw all stones
    for (auto& stone : this->stones) 
        target.draw(stone.sprite, states);

    // draw stone hightlight
    if (this->last_move.x != -1) 
        target.draw(this->red_dot, states);

    // draw stone hightlight
    if (this->last_highlight.x != -1) 
        target.draw(this->stone_sprite, states);
}

void Board::groupAdd(sf::Vector2i v, i32 color)
{
    bool added = false;
    std::vector<size_t> added_groups;
    for (auto i = 0; i < this->groups.size(); i++) {
        if (this->groups[i].canAdd(v, color)) {
            this->groups[i].addStone(v);
            added_groups.push_back(i);
            added = true;
        }
    }

    if (added) {
        StoneGroup combined_group(color);
        for (auto i : added_groups) {
            combined_group.combineGroups(groups[i]);
        }

        std::sort(added_groups.begin(), added_groups.end(), std::greater<size_t>());
        for (auto i : added_groups) {
            this->groups[i] = this->groups.back();
            this->groups.pop_back();
        }

        this->groups.push_back(combined_group);
    } else this->groups.push_back(StoneGroup(v, color));
}

void Board::groupErase(sf::Vector2i v) {
        std::vector<size_t> adjacent_groups;
    for (auto i = 0; i < groups.size(); i++) {
        if (groups[i].isAdjacent(v)) {   
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

            auto size = this->groups[i].getSize();
            auto state = this->groups[i].getState();

            if (state == 1) 
                this->score_white += size;
            else this->score_black += size;

            this->groups[i] = this->groups.back();
            this->groups.pop_back();
        }
    }

    for (auto it = groups.begin(); it != groups.end(); it++) {
        if (it->containsStone(v) && it->checkLibreties(stones, size) == 0) {
            it->removeStones(this->stones, this->size);
            groups.erase(it);
            break;
        }
    }
}

/// TODO: change: tile size and position of starting tile are hardcoded
void Board::makeMove(sf::Vector2f coords) {
    auto v = this->getPosFromCoords(coords);
    auto index = this->getIndexFromPos(v);
    auto& stone = this->stones[index];

    // start - 60
    // first line - 90 
    // tile size - 50
    if (stone.turn == 0) {
        stone.turn = this->turn;

        this->last_move = v;
        auto dot_offset = 90 - this->red_dot.getGlobalBounds().width / 2;
        this->red_dot.setPosition(sf::Vector2f(v.x * 50 + dot_offset, v.y * 50 + dot_offset));

        this->groupAdd(v, this->turn);

        if (this->turn == 1) 
            stone.sprite.setColor(sf::Color::Black);
        else stone.sprite.setColor(sf::Color::White);
        
        if (this->swap_turns) {
            if (this->turn == 1) this->turn = 2;
            else this->turn = 1;
        }

        if (Settings::enableSounds)
            this->stone_sound.play();
        this->groupErase(v);
    }

    if (Settings::enableLogging)
        std::cout << "click indexes: " << v.x << " " << v.y << "\n";
}

void Board::setHighlight(sf::Vector2f coords) {
    auto v = this->getPosFromCoords(coords);
    auto index = this->getIndexFromPos(v);

    this->last_highlight = v ;

    auto stone_offset = 90 - this->stone_sprite.getGlobalBounds().width / 2;
    this->stone_sprite.setPosition(sf::Vector2f(v.x * 50 + stone_offset, v.y * 50 + stone_offset));
    if (this->stones[index].turn != 0)
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

sf::Vector2i Board::getPosFromCoords(sf::Vector2f coords) {
    i32 unchecked_x = (coords.x - offset) / 50;
    i32 x = unchecked_x >= this->size ? this->size - 1 : unchecked_x;
    i32 unchecked_y = (coords.y - offset) / 50;
    i32 y = unchecked_y >= this->size ? this->size - 1 : unchecked_y;

    return sf::Vector2i(x, y);
}

sf::Vector2i Board::getPosFromIndex(i32 index) {
    auto y = index / this->size;
    auto x = (index - (y * this->size));
    return sf::Vector2i(x, y);
}

i32 Board::getIndexFromPos(sf::Vector2i pos) {
    return pos.x + this->size * pos.y;
}

// Serialization order:
//  - stones
//  - groups
//  - scores

std::ostream &operator<<(std::ostream& stream, const Board& board) {
    board.serialize(stream);
    board.saveImage();
    return stream;
}

std::istream &operator>>(std::istream& stream, Board& board) {
    board.deserialize(stream);
    return stream;
}

void Board::serialize(std::ostream& stream) const {
    for (auto& stone : this->stones) {
        stream.write((char*)&stone.turn, sizeof(stone.turn));
    }

    stream.write((char*)&this->score_black, sizeof(this->score_black));
    stream.write((char*)&this->score_white, sizeof(this->score_white));
}

void Board::deserialize(std::istream& stream) {
    this->groups.clear();
    this->last_move = sf::Vector2i(-1, -1);

    for (auto& stone : this->stones) {
        stream.read((char*)&stone.turn, sizeof(stone.turn));

        switch (stone.turn)
        {
        case 0: stone.sprite.setColor(sf::Color::Transparent); break;
        case 1: stone.sprite.setColor(sf::Color::Black); break;
        case 2: stone.sprite.setColor(sf::Color::White); break;
        }

        auto pos = this->getPosFromCoords(stone.sprite.getPosition());
        this->groupAdd(pos, stone.turn);
    }

    stream.read((char*)&this->score_black, sizeof(this->score_black));
    stream.read((char*)&this->score_white, sizeof(this->score_white));
}

void Board::saveImage() const {
    auto sprite_cpy = this->sprite;
    auto rect = this->sprite.getGlobalBounds();

    sf::RenderTexture render;
    std::cout << "Width: " << rect.width << " height: " << rect.height << "\n";

    if(!render.create(rect.width, rect.height)) {
        std::cerr << "Failed to create renderer";
        return;
    }

    sprite_cpy.setPosition(sf::Vector2f(0, 0));
    render.draw(sprite_cpy);

    for (auto stone : this->stones) {
        auto pos = stone.sprite.getPosition();
        stone.sprite.setPosition(sf::Vector2f(pos.x - offset, pos.y - offset));
        render.draw(stone.sprite);
    }

    auto img = render.getTexture().copyToImage();
    img.flipVertically();
    if (!img.saveToFile("board.png")) {
        std::cerr << "Failed to save board preview";
        return;
    }
}
