#include "Animation.hpp"

Animation::Animation(sf::Sprite* target) {
    this->current = 0;
    this->progress = 0;
    this->target = target;
}

Animation::~Animation() {
    
}

Animation::Animation() {
    
}

void Animation::addFrame(Frame&& frame) {
    this->frames.push_back(std::move(frame));
}

void Animation::update(f32 delta) {
    this->progress += delta;

    if (this->progress >= this->frames[this->current].duration) {
        this->progress = 0;

        this->target->setTextureRect(this->frames[this->current].rect);

        this->current++;

        if (this->current >= this->frames.size()) 
            this->current = 0;
    }
}
