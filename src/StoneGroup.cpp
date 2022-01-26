#include "StoneGroup.hpp"

StoneGroup::StoneGroup(sf::Vector2i pos, i32 state) {
    this->group.push_back(pos);
    this->state = state;
}

StoneGroup::StoneGroup(i32 state) {
    this->state = state;
}

StoneGroup::~StoneGroup() {

}


bool StoneGroup::canAdd(sf::Vector2i pos, i32 state) {
    if (this->state != state)
        return false;

    for (auto stone : this->group) {

        if (stone.x == pos.x) {
            if (stone.y == pos.y - 1 || stone.y == pos.y + 1) {
                return true;
            }
        } else if (stone.y == pos.y) {
            if (stone.x == pos.x - 1 || stone.x == pos.x + 1) {
                return true;
            }
        }
    }

    return false;
}

bool StoneGroup::isAdjacent(sf::Vector2i pos) {
    for (auto stone : this->group) {
        if (stone.x == pos.x) {
            if (stone.y == pos.y - 1 || stone.y == pos.y + 1) {
                return true;
            }
        } else if (stone.y == pos.y) {
            if (stone.x == pos.x - 1 || stone.x == pos.x + 1) {
                return true;
            }
        }
    }

    return false;
}

bool StoneGroup::sameState(i32 state) {
    return this->state == state;
}

bool StoneGroup::isEmpty() {
    return this->group.empty();
}

void StoneGroup::addStone(sf::Vector2i pos) {
    this->group.push_back(pos);
}

i32 StoneGroup::findStone(sf::Vector2i pos) {
    for (auto i = 0; i < this->group.size(); i++)
        if (this->group[i] == pos) return i;

    return -1;
}

bool StoneGroup::containsStone(sf::Vector2i pos) {
    if (this->findStone(pos) != -1) return true;
    else return false;
}

void StoneGroup::removeStones(std::vector<Stone>& stones, size_t size) {
    for (auto pos : this->group) {
        auto& stone = stones[pos.x + pos.y * size];
        stone.sprite.setColor(sf::Color::Transparent);
        stone.turn = 0;
    }
}


i32 StoneGroup::checkLibreties(
    const std::vector<Stone> &stones, size_t size) {
    i32 libreties = 0;

    for (auto stone : this->group)
    {
        i32 x = stone.x;
        i32 y = stone.y;

        if (x + 1 < size) {
            auto s = stones[x + 1 + size * y];
            if (s.turn == 0)
                libreties++;
        }

        if (x - 1 >= 0) {
            auto s = stones[x - 1 + size * y];
            if (s.turn == 0)
                libreties++;
        }

        if (y + 1 < size) {
            auto s = stones[x + size * (y + 1)];
            if (s.turn == 0)
                libreties++;
        }

        if (y - 1 >= 0 ) {
            auto s = stones[x + size * (y - 1)];
            if (s.turn == 0)
                libreties++;
        }
    }

    return libreties;
}

void StoneGroup::combineGroups(StoneGroup stone_group) {
    for (auto stone : stone_group.group)
        this->group.push_back(stone);
}

void combineGroups(std::vector<StoneGroup> groups, i32 i, i32 j) {
    auto& add_stones = groups[i];
    auto& del_stones = groups[j];

    for (auto stone : del_stones.group) {
        add_stones.group.push_back(stone);
    }
}

