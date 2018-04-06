#include "GUI/CheckBox.hpp"

namespace sf
{
    CheckBox::CheckBox(sf::Vector2f position,float s, sf::Color color, sf::Color mColor, sf::Color iColor, bool isActive)
    {
        sf::Vector2f size(0,s);
        active=isActive;
        markColor=mColor;
        inactiveColor=iColor;
        position=clientMath::scaleWithResolution(position);
        size=clientMath::scaleWithResolution(size);
        body.setFillColor(color);
        body.setPosition(sf::Vector2f(position.x,position.y));
        body.setSize(sf::Vector2f(size.y,size.y));
        if(isActive)
        mark.setFillColor(mColor);
        else
        mark.setFillColor(inactiveColor);
        mark.setPosition(sf::Vector2f(position.x+(size.y/3.5),position.y+(size.y/3.5)));
        mark.setSize(sf::Vector2f(size.y-(2*(size.y/3.5)),size.y-(2*(size.y/3.5))));
    }

    sf::Vector2f CheckBox::getPosition()
    {
        return body.getPosition();
    }

    sf::Vector2f CheckBox::getSize()
    {
        return body.getSize();
    }

    bool CheckBox::isActive()
    {
        return active;
    }

    bool CheckBox::isClicked(sf::Vector2i pos)
    {
        if((pos.x>=getPosition().x && pos.x<=getPosition().x+getSize().x)&&(pos.y>=getPosition().y && pos.y<=getPosition().y+getSize().y))
        return true;
        else
        return false;
    }

    void CheckBox::setActive(bool var)
    {
        if(var==true)
        mark.setFillColor(markColor);
        else
        mark.setFillColor(inactiveColor);
        active=var;
    }

    void CheckBox::setPosition(sf::Vector2f pos)
    {
        sf::Vector2f distance=pos-body.getPosition();
        body.setPosition(pos.x,pos.y);
        mark.setPosition(mark.getPosition()+distance);
    }

    void CheckBox::draw(sf::RenderWindow &window)
    {
        window.draw(body);
        window.draw(mark);
    }
}
