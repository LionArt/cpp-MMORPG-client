#include "GUI/Spinner.hpp"

namespace sf
{
    Spinner::Spinner(sf::Vector2f position,sf::Vector2f size, sf::Color color,sf::Color buttonColor, unsigned int var, unsigned int maxVar,std::string title,std::string f,float percentageFontSize, sf::Color textColor, sf::Text::Style style)
    {
        font=f;
        text=GUI::Text::createDefaultText(title,font,textColor,percentageFontSize,position,style);
        position=clientMath::scaleWithResolution(position);
        size=clientMath::scaleWithResolution(size);
        TextModule::fitContainer(text,font,position,size);
        body.setFillColor(color);
        body.setPosition(position);
        body.setSize(size);
        body.setOutlineColor(sf::Color::Black);
        body.setOutlineThickness(1);
        leftButton.setFillColor(color);
        leftButton.setSize(sf::Vector2f(size.y,size.y));
        leftButton.setPosition(sf::Vector2f(position.x-size.y-1,position.y));
        leftButton.setOutlineColor(sf::Color::Black);
        leftButton.setOutlineThickness(1);
        rightButton.setFillColor(color);
        rightButton.setSize(sf::Vector2f(size.y,size.y));
        rightButton.setPosition(sf::Vector2f(position.x+size.x+1,position.y));
        rightButton.setOutlineColor(sf::Color::Black);
        rightButton.setOutlineThickness(1);
        rightIcon=sf::CircleShape(size.y/3,3);
        rightIcon.setFillColor(buttonColor);
        rightIcon.rotate(90);
        rightIcon.setPosition(rightButton.getPosition());
        rightIcon.move(size.y-rightIcon.getRadius()/2,rightIcon.getRadius()/2);
        leftIcon=sf::CircleShape(size.y/3,3);
        leftIcon.setFillColor(buttonColor);
        leftIcon.rotate(270);
        leftIcon.setPosition(leftButton.getPosition());
        leftIcon.move(leftIcon.getRadius()/2,size.y-leftIcon.getRadius()/2);
    }

    sf::Vector2f Spinner::getPosition()
    {
        return leftButton.getPosition();
    }

    sf::Vector2f Spinner::getSize()
    {
        return sf::Vector2f(leftButton.getSize().x+body.getSize().x+rightButton.getSize().x,body.getSize().y);
    }

    unsigned int Spinner::getValue()
    {
        return value;
    }

    void Spinner::setValue(unsigned int var)
    {
        value=var;
    }

    void Spinner::setPosition(sf::Vector2f pos)
    {
        sf::Vector2f distance=pos-body.getPosition();
        body.setPosition(pos.x,pos.y);
        leftButton.setPosition(leftButton.getPosition()+distance);
        rightButton.setPosition(rightButton.getPosition()+distance);
        leftIcon.setPosition(leftIcon.getPosition()+distance);
        rightIcon.setPosition(rightIcon.getPosition()+distance);
        TextModule::fitContainer(text,font,body.getPosition(),body.getSize());
    }

    void Spinner::centerResolutionWidth()
    {
        setPosition(sf::Vector2f((round(body.getPosition().x+((0+((float(VideoSettings::CurrentVideoMode.width))/2))-body.getPosition().x-(float(body.getSize().x)/2))))-1,body.getPosition().y));
    }

    void Spinner::draw(sf::RenderWindow &window)
    {
        window.draw(body);
        window.draw(text);
        window.draw(leftButton);
        window.draw(rightButton);
        window.draw(rightIcon);
        window.draw(leftIcon);
    }
}
