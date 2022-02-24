#ifndef IGUICOMPONENT_H
#define IGUICOMPONENT_H

#include "SFML/Graphics.hpp"
#include "Types.hpp"


class GuiComponent : public sf::Drawable {
    
public:
    virtual ~GuiComponent() = 0;
    virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const = 0;
    virtual void update() = 0;
};

#endif