#include "GUI/Interface.hpp"

namespace sf
{
    Interface::Interface(sf::Vector2f position,sf::Vector2f size, sf::Color color, sf::Color titleColor, std::string t,std::string font,float percentageFontSize, sf::Color textColor, sf::Text::Style style)
    {
        textFont=font;
        text=GUI::Text::createDefaultText(t,font,textColor,percentageFontSize,position,style);
        position=clientMath::scaleWithResolution(position);
        size=clientMath::scaleWithResolution(size);
        title.setSize(sf::Vector2f(size.x,VideoSettings::CurrentVideoMode.width/100*percentageFontSize+2));
        bodyBorder.setSize(size);
        bodyBorder.setPosition(position);
        bodyBorder.setFillColor(color);
        bodyBorder.setOutlineColor(titleColor);
        bodyBorder.setOutlineThickness(1);
        title.setPosition(position);
        title.setFillColor(titleColor);
        TextModule::fitContainer(text,font,title.getPosition(),title.getSize());
    }

    sf::Vector2f Interface::getPosition()
    {
        return title.getPosition();
    }

    void Interface::draw(sf::RenderWindow &window)
    {
        window.draw(bodyBorder);
        window.draw(title);
        window.draw(text);
        for(unsigned int i=0;i<interfaces.size();i++)
        interfaces[i].draw(window);
        for(unsigned int i=0;i<checkboxes.size();i++)
        checkboxes[i].draw(window);
        for(unsigned int i=0;i<sliders.size();i++)
        sliders[i].draw(window);
        for(unsigned int i=0;i<spinners.size();i++)
        spinners[i].draw(window);
        for(unsigned int i=0;i<buttons.size();i++)
        buttons[i].draw(window);
        for(unsigned int i=0;i<textboxes.size();i++)
        textboxes[i].draw(window);
        for(unsigned int i=0;i<texts.size();i++)
        window.draw(texts[i]);
    }

    void Interface::addText(sf::Text text)
    {
        texts.push_back(text);
    }

    void Interface::addButton(sf::Button button)
    {
        buttons.push_back(button);
    }

    void Interface::addTextBox(sf::TextBox textBox)
    {
        textboxes.push_back(textBox);
    }

    void Interface::setTitle(std::string newString)
    {
        text.setString(newString);
        TextModule::fitContainer(text,textFont,title.getPosition(),title.getSize());
    }

    void Interface::setPosition(sf::Vector2f pos)
    {
        sf::Vector2f distance=pos-title.getPosition();
        bodyBorder.setPosition(pos);
        title.setPosition(pos);
        TextModule::fitContainer(text,textFont,title.getPosition(),title.getSize());
        for(unsigned int i=0;i<interfaces.size();i++)
        interfaces[i].setPosition(interfaces[i].getPosition()+distance);
        for(unsigned int i=0;i<checkboxes.size();i++)
        checkboxes[i].setPosition(checkboxes[i].getPosition()+distance);
        for(unsigned int i=0;i<sliders.size();i++)
        sliders[i].setPosition(sliders[i].getPosition()+distance);
        for(unsigned int i=0;i<spinners.size();i++)
        spinners[i].setPosition(spinners[i].getPosition()+distance);
        for(unsigned int i=0;i<buttons.size();i++)
        buttons[i].setPosition(buttons[i].getPosition()+distance);
        for(unsigned int i=0;i<textboxes.size();i++)
        textboxes[i].setPosition(textboxes[i].getPosition()+distance);
        for(unsigned int i=0;i<texts.size();i++)
        texts[i].setPosition(texts[i].getPosition()+distance);
        TextModule::fitContainer(text,textFont,title.getPosition(),title.getSize());
    }

    void Interface::centerResolutionWidth()
    {
        setPosition(sf::Vector2f((round(bodyBorder.getPosition().x+((0+((float(VideoSettings::CurrentVideoMode.width))/2))-bodyBorder.getPosition().x-(float(bodyBorder.getSize().x)/2))))-1,bodyBorder.getPosition().y));
    }

}

namespace GUI
{
    namespace Interface
    {
        sf::Interface createFullscreenInterface(std::string title, bool visible)
        {
            sf::Interface visibleInterface=sf::Interface(sf::Vector2f(0,0),sf::Vector2f(100,100),InterfaceSettings::InterfaceBodyColor,InterfaceSettings::InterfaceTitleBarColor,title,DEFAULT_FONT,3,InterfaceSettings::InterfaceTitleTextColor);
            sf::Interface invisibileInterface=sf::Interface(sf::Vector2f(0,0),sf::Vector2f(100,100),sf::Color::Transparent,sf::Color::Transparent,title,DEFAULT_FONT,3,sf::Color::Transparent);
            if(visible)
            return visibleInterface;
            else
            return invisibileInterface;
        }

        sf::Interface createCreditsInterface(std::string title, bool visible)
        {
            sf::Interface visibleInterface=sf::Interface(sf::Vector2f(20,19),sf::Vector2f(60,60),InterfaceSettings::CreditsInterfaceBodyColor,InterfaceSettings::InterfaceTitleBarColor,title,DEFAULT_FONT,3,InterfaceSettings::InterfaceTitleTextColor);
            sf::Interface invisibileInterface=sf::Interface(sf::Vector2f(20,19),sf::Vector2f(60,60),sf::Color::Transparent,sf::Color::Transparent,title,DEFAULT_FONT,3,sf::Color::Transparent);
            if(visible)
            return visibleInterface;
            else
            return invisibileInterface;
        }

        sf::Interface createCharacterSelect(std::string title, bool visible)
        {
            sf::Interface visibleInterface=sf::Interface(sf::Vector2f(40,24),sf::Vector2f(20,45),InterfaceSettings::CreditsInterfaceBodyColor,InterfaceSettings::InterfaceTitleBarColor,title,DEFAULT_FONT,3,InterfaceSettings::InterfaceTitleTextColor);
            sf::Interface invisibileInterface=sf::Interface(sf::Vector2f(40,24),sf::Vector2f(20,45),sf::Color::Transparent,sf::Color::Transparent,title,DEFAULT_FONT,3,sf::Color::Transparent);
            if(visible)
            return visibleInterface;
            else
            return invisibileInterface;
        }

        sf::Interface createConnectionInterface(std::string title, bool visible)
        {
            sf::Interface visibleInterface=sf::Interface(sf::Vector2f(18,37),sf::Vector2f(64,20),InterfaceSettings::CreditsInterfaceBodyColor,InterfaceSettings::InterfaceTitleBarColor,title,DEFAULT_FONT,3,InterfaceSettings::InterfaceTitleTextColor);
            sf::Interface invisibileInterface=sf::Interface(sf::Vector2f(18,37),sf::Vector2f(64,20),sf::Color::Transparent,sf::Color::Transparent,title,DEFAULT_FONT,3,sf::Color::Transparent);
            if(visible)
            return visibleInterface;
            else
            return invisibileInterface;
        }
    }
}


