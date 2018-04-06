#include "GUI/Slider.hpp"

namespace sf
{
    Slider::Slider(sf::Vector2f position,sf::Vector2f size, sf::Vector2f indicatorSize,sf::Color color, sf::Color iColor, float var, float maxVar, float minVar, bool autosize)
    {
        value=var;
        maxValue=maxVar;
        minValue=minVar;
        indicatorColor=iColor;
        position=clientMath::scaleWithResolution(position);
        size=clientMath::scaleWithResolution(size);
        bar.setFillColor(color);
        bar.setOutlineColor(sf::Color::Black);
        bar.setOutlineThickness(2);
        bar.setPosition(sf::Vector2f(position.x,position.y));
        bar.setSize(sf::Vector2f(size.x,size.y));
        indicator.setFillColor(indicatorColor);
        indicator.setOutlineColor(sf::Color::Black);
        indicator.setOutlineThickness(2);
        //0=pozycja bara, 100=pozycja bara+szerokosc-szerokosc kursora
        //pozycjaBara.x+(((szerokosc bara-szerokosc kursora)/100)*var)
        if(autosize)
        indicator.setSize(sf::Vector2f((size.x/100)*((100/maxValue)*(minValue))+1,(size.y/100)*indicatorSize.y));
        else
        indicator.setSize(sf::Vector2f((size.x/100)*indicatorSize.x,(size.y/100)*indicatorSize.y));
        indicator.setPosition(sf::Vector2f(bar.getPosition().x+(((bar.getSize().x-indicator.getSize().x)/100)*((100/maxValue)*(value-minValue))),bar.getPosition().y-(indicator.getSize().y-bar.getSize().y)/2));
    }

    sf::Vector2f Slider::getPosition()
    {
        return bar.getPosition();
    }

    sf::Vector2f Slider::getSize()
    {
        return bar.getSize();
    }

    float Slider::getValue()
    {
        return value;
    }

    void Slider::setValue(float var)
    {
        if(var>=minValue)
        {
            if(var>maxValue)
            value=maxValue;
            else
            value=var;
        }
        else
        value=minValue;
        indicator.setPosition(sf::Vector2f(bar.getPosition().x+(((bar.getSize().x-indicator.getSize().x)/100)*((100/maxValue)*(value-minValue))),indicator.getPosition().y));
    }

    void Slider::setPosition(sf::Vector2f pos)
    {
        sf::Vector2f distance=pos-bar.getPosition();
        bar.setPosition(pos.x,pos.y);
        indicator.setPosition(indicator.getPosition()+distance);
    }

    void Slider::centerResolutionWidth()
    {
        setPosition(sf::Vector2f((round(bar.getPosition().x+((0+((float(VideoSettings::CurrentVideoMode.width))/2))-bar.getPosition().x-(float(bar.getSize().x)/2))))-1,bar.getPosition().y));
    }

    void Slider::draw(sf::RenderWindow &window)
    {
        window.draw(bar);
        window.draw(indicator);
    }
}
