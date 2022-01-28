#include "gui/Button.hpp"

Button::Button() { }
Button::~Button() { }

Button::Button(sf::Font font, const sf::Vector2f& size) {
    this->caption.setFont(font);
    this->base.setSize(size);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->base, states);
    target.draw(this->caption, states);
}

void Button::update(sf::Vector2f click_pos) {
    auto pos = this->base.getGlobalBounds();
    if (click_pos.x > pos.left && click_pos.x > pos.left + pos.width
        && click_pos.y > pos.top && click_pos.y > pos.top + pos.height) {
            this->clicked = true;
    } else this->clicked = false;
}

void Button::update() {

}

bool Button::clickCallback() {
    return this->clicked;
}

void Button::setText(std::string text) {
    this->caption.setString(text);
}

void Button::setBackground(sf::Color color) {
    this->base.setFillColor(color);
}

void Button::setOutlineThickness(f32 thicc) {
    this->caption.setOutlineThickness(thicc);
}

void Button::setOutlineColor(sf::Color color) {
    this->base.setOutlineColor(color);
}

void Button::setPosition(const sf::Vector2f& position) {
    this->base.setPosition(position);
    // set font size so the caption always perfectly fits in a button
    this->caption.setCharacterSize(30);
    this->caption.setPosition(position);
}
