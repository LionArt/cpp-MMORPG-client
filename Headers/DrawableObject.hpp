#ifndef DRAWABLE_OBJECT_HPP
#define DRAWABLE_OBJECT_HPP

#include "SFML/Graphics.hpp"

class DrawableObject
{
    public:
    virtual void draw(sf::RenderWindow&)=0;
};

#endif // DRAWABLE_OBJECT_HPP
