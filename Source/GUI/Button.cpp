#include "GUI/Button.hpp"

namespace sf
{
    Button::Button(sf::Vector2f position,sf::Vector2f size, sf::Color color,std::string title,std::string font,float percentageFontSize, sf::Color textColor, sf::Text::Style style)
    {
        textFont=font;
        text=GUI::Text::createDefaultText(title,textFont,textColor,percentageFontSize,position,style);
        position=clientMath::scaleWithResolution(position);
        size=clientMath::scaleWithResolution(size);
        TextModule::fitContainer(text,font,position,size);
        body.setFillColor(color);
        body.setPosition(position);
        body.setSize(size);
    }

    sf::Vector2f Button::getPosition()
    {
        return body.getPosition();
    }

    sf::Vector2f Button::getSize()
    {
        return body.getSize();
    }

    std::string Button::getTitle()
    {
        return text.getString();
    }

    bool Button::isClicked(sf::Vector2i pos)
    {
        if((pos.x>=getPosition().x && pos.x<=getPosition().x+getSize().x)&&(pos.y>=getPosition().y && pos.y<=getPosition().y+getSize().y))
        return true;
        else
        return false;
    }

    void Button::setTitle(std::string newString)
    {
        text.setString(newString);
        TextModule::fitContainer(text,textFont,body.getPosition(),body.getSize());
    }

    void Button::setPosition(sf::Vector2f pos)
    {
        body.setPosition(pos.x,pos.y);
        TextModule::fitContainer(text,textFont,body.getPosition(),body.getSize());
    }

    void Button::centerResolutionWidth()
    {
        setPosition(sf::Vector2f((round(body.getPosition().x+((0+((float(VideoSettings::CurrentVideoMode.width))/2))-body.getPosition().x-(float(body.getSize().x)/2))))-1,body.getPosition().y));
    }

    void Button::setTextColor(sf::Color color)
    {
        text.setColor(color);
    }

    void Button::draw(sf::RenderWindow &window)
    {
        window.draw(body);
        window.draw(text);
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
            sf::Button button=sf::Button(position,ButtonSettings::MenuButtonSize,ButtonSettings::ButtonColor,title,DEFAULT_FONT,BUTTON_CHARACTER_SIZE,ButtonSettings::ButtonTextColor);
            return button;
        }

        sf::Button createCharacterSelectButton(std::string title, sf::Vector2f position)
        {
            if(title.length()>MENU_BUTTON_MAX_CHARACTERS)
            title.erase(MENU_BUTTON_MAX_CHARACTERS);
            sf::Button button=sf::Button(position,ButtonSettings::CharacterSelectButtonSize,ButtonSettings::ButtonColor,title,DEFAULT_FONT,CHARACTER_SELECT_BUTTON_CHAR_SIZE,ButtonSettings::ButtonTextColor);
            return button;
        }
    }
}
