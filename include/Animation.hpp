#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "Types.hpp"

struct Frame {
    sf::IntRect rect;
    f32 duration;
};

class Animation {
private:
    i32 current;
    f32 progress;
    std::vector<Frame> frames;
    sf::Sprite* target;

public:
    Animation(sf::Sprite* target);
    Animation();
    ~Animation();
    void update(f32 delta);
    void addFrame(sf::Sprite sprite, f32 duration);
    void addFrame(Frame&&);
};

#endif