#include "GUI/TextBox.hpp"

namespace sf
{
     TextBox::TextBox(sf::Vector2f position,sf::Vector2f size, sf::Color color,std::string f,float percentageFontSize, sf::Color textColor, sf::Text::Style style, bool isActive, bool isEncrypted)
    {
        textValue="";
        font=f;
        active=isActive;
        encrypted=isEncrypted;
        position=clientMath::scaleWithResolution(position);
        size=clientMath::scaleWithResolution(size);
        cursor.setFillColor(textColor);
        cursor.setSize(sf::Vector2f(1,(clientMath::scaleFontSize(VideoSettings::CurrentVideoMode.height,percentageFontSize))));
        if(isEncrypted)
        percentageFontSize=percentageFontSize+2;
        text=GUI::Text::createDefaultText("",f,textColor,percentageFontSize);
        TextModule::fitContainer(text,font,position,size);
        cursor.setPosition(sf::Vector2f(TextModule::getExactPos(text,font).x+TextModule::getExactSize(text,font).x+(VideoSettings::CurrentVideoMode.width/400)*1,position.y+((size.y-cursor.getSize().y)/2)));
        body.setFillColor(color);
        body.setPosition(sf::Vector2f(position.x,position.y));
        body.setSize(sf::Vector2f(size.x,size.y));
    }

    sf::Vector2f TextBox::getPosition()
    {
        return body.getPosition();
    }

    sf::Vector2f TextBox::getSize()
    {
        return body.getSize();
    }

    std::string TextBox::getText()
    {
        return text.getString();
    }

    std::string TextBox::getTextValue()
    {
        return textValue;
    }

    bool TextBox::isActive()
    {
        return active;
    }

    bool TextBox::isClicked(sf::Vector2i pos)
    {
        if((pos.x>=getPosition().x && pos.x<=getPosition().x+getSize().x)&&(pos.y>=getPosition().y && pos.y<=getPosition().y+getSize().y))
        return true;
        else
        return false;
    }

    void TextBox::setText(std::string newString)
    {
        std::string n="";
        if(encrypted)
        {
            for(int i=0;i<newString.length();i++)
            {
                n=n+"*";
            }
            text.setString(n);
            TextModule::centerHeightOnly(text,font,body.getPosition(),body.getSize());
        }
        else
        {
            text.setString("W");
            TextModule::centerHeightOnly(text,font,body.getPosition(),body.getSize());
            text.setString(newString);
        }
        textValue=newString;
        TextModule::centerWidthOnly(text,font,body.getPosition(),body.getSize());
        cursor.setPosition(TextModule::getExactPos(text,font).x+TextModule::getExactSize(text,font).x+(VideoSettings::CurrentVideoMode.width/400)*1,cursor.getPosition().y);
    }

    void TextBox::setTextValue(std::string newString)
    {
        textValue=newString;
    }

    void TextBox::setPosition(sf::Vector2f pos)
    {
        sf::Vector2f distance=pos-body.getPosition();
        body.setPosition(pos.x,pos.y);
        TextModule::fitContainer(text,font,body.getPosition(),body.getSize());
        cursor.setPosition(cursor.getPosition()+distance);
    }

    void TextBox::centerResolutionWidth()
    {
        setPosition(sf::Vector2f((round(body.getPosition().x+((0+((float(VideoSettings::CurrentVideoMode.width))/2))-body.getPosition().x-(float(body.getSize().x)/2))))-1,body.getPosition().y));
    }

    void TextBox::setTextColor(sf::Color color)
    {
        text.setColor(color);
    }

    void TextBox::setActive(bool var)
    {
        active=var;
    }

    void TextBox::draw(sf::RenderWindow &window)
    {
        window.draw(body);
        window.draw(text);
        if(isActive())
        {
            time_t seconds;
            seconds=time(NULL);
            if((int)seconds%2>0)
            window.draw(cursor);
        }
    }
}

namespace GUI
{
    namespace TextBox
    {
        sf::TextBox createLoginTextBox(sf::Vector2f position,bool isEncrypted)
        {
            sf::TextBox textBox=sf::TextBox(position,TextBoxSettings::TextBoxSize, TextBoxSettings::TextBoxColor,DEFAULT_FONT,TEXTBOX_CHARACTER_SIZE,TextSettings::MenuGrayColor, sf::Text::Style::Regular,false,isEncrypted);
            textBox.centerResolutionWidth();
            return textBox;
        }

        sf::TextBox createChatTextBox()
        {
            sf::TextBox textBox=sf::TextBox(sf::Vector2f(35,65),TextBoxSettings::ChatSize, TextBoxSettings::ChatColor,DEFAULT_FONT,CHAT_CHARACTER_SIZE,TextSettings::MessageColor, sf::Text::Style::Regular,true,false);
            return textBox;
        }
    }
}
