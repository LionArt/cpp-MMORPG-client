#ifndef GUIOBJECT_HPP
#define GUIOBJECT_HPP

#include "DrawableObject.hpp"

class GUIObject:public DrawableObject
{
    public:
    virtual void draw(sf::RenderWindow&)=0;
    virtual void setPosition(sf::Vector2f)=0;
    virtual sf::Vector2f getPosition()=0;
    virtual sf::Vector2f getSize()=0;
    virtual void centerResolutionWidth()=0;
};

#endif // GUIOBJECT_HPP
