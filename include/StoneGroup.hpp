#ifndef STONEGROUP_H
#define STONEGROUP_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "Types.hpp"
#include "Stone.hpp"


class StoneGroup {
private:
    std::vector<sf::Vector2i> group;
    // State represents color of all stones in a group
    i32 state;

public:
    StoneGroup(sf::Vector2i pos, i32 state);
    StoneGroup(i32 state);
    ~StoneGroup();

    // Checks whether stone can be added to a group
    bool canAdd(sf::Vector2i pos, i32 state);
    bool isAdjacent(sf::Vector2i pos);

    size_t getSize();
    i32 getState();

    bool isEmpty();

    bool sameState(i32 state);

    // Check and return number of free spaces around a group
    i32 checkLibreties(const std::vector<Stone>&, size_t);

    void addStone(sf::Vector2i pos);
    i32 findStone(sf::Vector2i pos);
    bool containsStone(sf::Vector2i pos);

    void removeStones(std::vector<Stone>&, size_t);

    void combineGroups(StoneGroup group);
    // Combine two groups, add all elements to first group and remove the second
    friend void combineGroups(std::vector<StoneGroup> groups, i32 i, i32 j);
};

#endif