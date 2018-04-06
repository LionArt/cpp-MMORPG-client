#include "Button.h"

namespace sf
{
    Button::Button(sf::Vector2f position,sf::Vector2f size, sf::Color color,std::string title,std::string font,float percentageFontSize, sf::Color textColor, sf::Text::Style style)
    {
        textFont=font;
        text=GUI::Text::createDefaultText(title,textFont,textColor,percentageFontSize);
        position=clientMath::scaleWithResolution(position);
        size=clientMath::scaleWithResolution(size);
        TextModule::fitContainer(text,font,position,size);
        body.setFillColor(color);
        body.setPosition(sf::Vector2f(position.x,position.y));
        body.setSize(sf::Vector2f(size.x,size.y));
    }

    std::string Button::getText()
    {
        return text.getString();
    }

    void Button::setPosition(sf::Vector2f pos)
    {
        body.setPosition(pos.x,pos.y);
        TextModule::fitContainer(text,textFont,body.getPosition(),body.getSize());
    }

    void Button::setText(std::string newString)
    {
        text.setString(newString);
        TextModule::fitContainer(text,textFont,body.getPosition(),body.getSize());
    }

    void Button::centerResolutionWidth()
    {
        setPosition(sf::Vector2f((round(body.getPosition().x+((0+((float(DefaultSettings::CurrentVideoMode.width))/2))-body.getPosition().x-(float(body.getSize().x)/2))))-1,body.getPosition().y));
    }

    bool Button::isClicked(sf::Vector2i pos)
    {
        if (((pos.x>=body.getPosition().x) && (pos.x<=body.getPosition().x+body.getSize().x)) && ((pos.y>=body.getPosition().y) && (pos.y<=body.getPosition().y+body.getSize().y)))
        return true;
        else
        return false;
    }
}

namespace GUI
{
    namespace Button
    {
        sf::Button createMenuButton(std::string title, sf::Vector2f position)
        {
            if(title.length()>MENU_BUTTON_MAX_CHARACTERS)
            title.erase(MENU_BUTTON_MAX_CHARACTERS);
            sf::Button button=sf::Button(position,DefaultSettings::ButtonSize,DefaultSettings::ButtonColor,title,DEFAULT_FONT,BUTTON_CHARACTER_SIZE,DefaultSettings::ButtonTextColor);
            return button;
        }
    }
}
