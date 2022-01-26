#ifndef IGUICOMPONENT_H
#define IGUICOMPONENT_H

#include "SFML/Graphics.hpp"
#include "Types.hpp"


class IGuiComponent : public sf::Drawable {
    
public:
    virtual ~IGuiComponent() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual void update() = 0;
    virtual void pollEvents() = 0;
};

#endif