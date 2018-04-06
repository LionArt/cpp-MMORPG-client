#include "GUI/Text.hpp"


namespace GUI
{
    namespace Text
    {
        sf::Text createDefaultText(std::string str, std::string font, sf::Color color, float percentageFontSize, sf::Vector2f percentagePosition, sf::Text::Style style)
        {
            sf::Text text;
            text.setFont(ResourceContainers::fonts[font]);
            text.setString(str);
            text.setStyle(style);
            sf::Vector2f textPosition=clientMath::scaleWithResolution(percentagePosition);
            text.setPosition(textPosition);
            text.setFillColor(color);
            int fontSize=clientMath::scaleFontSize(VideoSettings::CurrentVideoMode.height,percentageFontSize);
            text.setCharacterSize(fontSize);
            TextModule::correctOffset(text,font);
            return text;
        }

        std::vector<sf::Text> createMenuInfoText(std::string str,sf::Vector2f position)
        {
            std::vector<sf::Text> texts=createDimensionalText(str,DEFAULT_FONT,TextSettings::MenuInfoColor,MENU_INFO_CHARACTER_SIZE,position);
            return texts;
        }

        std::vector<sf::Text> createMessage(std::string str,sf::Vector2f position,std::string owner)
        {
            std::vector<sf::Text> texts=createDimensionalText(owner+": "+str,DEFAULT_FONT,TextSettings::MessageColor,MESSAGE_CHARACTER_SIZE,position);
            return texts;
        }

        std::vector<sf::Text> createCreditsInfoText(std::string str,sf::Vector2f position)
        {
            std::vector<sf::Text> texts=createDimensionalText(str,DEFAULT_FONT,TextSettings::MenuInfoColor,CREDITS_INFO_CHARACTER_SIZE,position);
            return texts;
        }

        std::vector<sf::Text> createCharacterNames(std::string str,sf::Vector2f position)
        {
            std::vector<sf::Text> texts=createDimensionalText(str,DEFAULT_FONT,sf::Color::White,CHARACTER_SELECT_CHAR_SIZE,position);
            return texts;
        }

        std::vector<sf::Text> createPlayerName(std::string str,sf::Vector2f position)
        {
            std::vector<sf::Text> texts=createDimensionalText(str,DEFAULT_FONT,TextSettings::MenuInfoColor,PLAYER_NAME_CHAR_SIZE,position);
            return texts;
        }

        std::vector<sf::Text> createDimensionalText(std::string str, std::string font, sf::Color color, float percentageFontSize, sf::Vector2f percentagePosition, sf::Text::Style style)
        {
            std::vector <sf::Text> texts;
            int shadowMod,lightMod;
            clientMath::calcDimResolutionMod(shadowMod,lightMod);
            sf::Color lightFontColor=clientMath::calcColorChange(color,-3,-18,43);
            sf::Text text=createDefaultText(str,font,color,percentageFontSize,percentagePosition,style);
            color=sf::Color::Black;
            sf::Text shadowText=createDefaultText(str,font,color,percentageFontSize,percentagePosition,style);
            color=lightFontColor;
            sf::Text lightText=createDefaultText(str,font,color,percentageFontSize,percentagePosition,style);
            shadowText.setPosition(shadowText.getPosition().x-shadowMod,shadowText.getPosition().y+shadowMod);
            lightText.setPosition(lightText.getPosition().x,lightText.getPosition().y+lightMod);
            texts.push_back(text);
            texts.push_back(shadowText);
            texts.push_back(lightText);
            return texts;
        }

        std::vector<sf::Text> createTitle(std::string title,float percentageFontSize, sf::Vector2f percentagePosition)
        {
            std::vector<sf::Text> texts=createDimensionalText(title,DEFAULT_FONT,TextSettings::TitleColor,percentageFontSize,percentagePosition);
            for(int i=0;i<texts.size();i++)
            TextModule::centerResolutionWidth(texts[i],DEFAULT_FONT);
            return texts;
        }
    }
}

namespace TextModule
{
    bool isClicked(sf::Text text, std::string font,sf::Vector2i pos)
    {
        sf::RectangleShape rect=getBoundaryBox(text,font);
        if((pos.x>=rect.getPosition().x && pos.x<=rect.getPosition().x+rect.getSize().x)&&(pos.y>=rect.getPosition().y && pos.y<=rect.getPosition().y+rect.getSize().y))
        return true;
        else
        return false;
    }

    //Pobiera limity wielkosci tekstu zalezne od czcionki
    sf::RectangleShape getBoundaryBox(sf::Text text,std::string font)
    {
        sf::RectangleShape shape;
        sf::Vector2f size;
        sf::Vector2f pos;
        int modX=0,modY=0;
        int boundboundaryBoxXOffset=0,boundboundaryBoxYOffset=0;
        if(font=="storybook")
        {
            modY=float(text.getCharacterSize())/4.1-1;
            boundboundaryBoxYOffset=2;
        }
        pos=sf::Vector2f(text.getPosition().x+modX,text.getPosition().y+modY);
        size=sf::Vector2f(text.getGlobalBounds().width+boundboundaryBoxXOffset,text.getGlobalBounds().height+boundboundaryBoxYOffset);
        shape.setPosition(pos);
        shape.setSize(size);
        return shape;
    }

    //Wyznaczanie prawdziwej pozycji tekstu zalezne od czcionki
    sf::Vector2f getExactPos(sf::Text text,std::string font)
    {
        sf::RectangleShape shape=getBoundaryBox(text,font);
        return shape.getPosition();
    }

    //Rozmiar okna limitu tekstu
    sf::Vector2f getExactSize(sf::Text text,std::string font)
    {
        sf::RectangleShape shape=getBoundaryBox(text,font);
        return shape.getSize();
    }

    //Ustawia tekst na srodku danego pojemnika (Button/Label/Title etc.)
    void fitContainer(sf::Text &text,std::string font,sf::Vector2f containerPos, sf::Vector2f containerSize)
    {
        centerWidthOnly(text,font,containerPos,containerSize);
        centerHeightOnly(text,font,containerPos,containerSize);
    }

    void centerHeightOnly(sf::Text &text, std::string font, sf::Vector2f containerPos, sf::Vector2f containerSize)
    {
        text.setPosition (text.getPosition().x,round(text.getPosition().y+((containerPos.y+((float(containerSize.y))/2))-(getExactPos(text,font).y+(float(text.getGlobalBounds().height)/2)))));
    }

    void centerWidthOnly(sf::Text &text, std::string font, sf::Vector2f containerPos, sf::Vector2f containerSize)
    {
        text.setPosition (round(text.getPosition().x+((containerPos.x+((float(containerSize.x))/2))-(getExactPos(text,font).x+(float(text.getGlobalBounds().width)/2)))),text.getPosition().y);
    }

    //Poprawa pozycji w oparciu o prawdziwa pozycje
    void correctOffset(sf::Text &text, std::string font)
    {
        sf::Vector2f pos(text.getPosition().x,getExactPos(text,font).y-text.getPosition().y);
        text.setPosition(text.getPosition().x,text.getPosition().y-pos.y);
    }

    //Wyœrodkowanie tekstu na ekranie
    void centerResolutionWidth (sf::Text &text, std::string font)
    {
         fitContainer(text,font,sf::Vector2f(0,getBoundaryBox(text,font).getPosition().y),sf::Vector2f(VideoSettings::CurrentVideoMode.width,text.getGlobalBounds().height));
    }
}
