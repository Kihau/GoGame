#ifndef BUTTON_H
#define BUTTON_H

#include "gui/GuiComponent.hpp"

// TODO: To implement either of the systems
// 1. Add c#-like callback event system (and use lamba expression to add callbacks)
// 2. Create fields for all button events, return their reault via callback methods (if callback method return true - execute some code)
// 3. Create sfml like event handling method (button.pollEvents())

class Button : public GuiComponent {
private:
    sf::Text caption;
    sf::RectangleShape base;
    bool clicked = false;

public:
    Button();
    Button(sf::Font font, const sf::Vector2f& size = sf::Vector2f(0.0f, 0.0f));
    ~Button();
    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;
    void update(sf::Vector2f);
    void update();
    bool clickCallback();

    void setText(std::string);
    void setBackground(sf::Color);
    void setOutlineThickness(f32);
    void setOutlineColor(sf::Color);
    void setPosition(const sf::Vector2f&);
};

#endif