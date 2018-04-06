#ifndef TEXT_HPP
#define TEXT_HPP

#include "SFML/Graphics.hpp"
#include "ResourceContainers.hpp"
#include "ClientMath.hpp"

namespace GUI
{
    namespace Text
    {
        sf::Text createDefaultText(std::string text, std::string font, sf::Color color, float percentageFontSize, sf::Vector2f percentagePosition=sf::Vector2f(1,1), sf::Text::Style style=sf::Text::Style::Regular);
        std::vector<sf::Text> createMenuInfoText(std::string str,sf::Vector2f position);
        std::vector<sf::Text> createCreditsInfoText(std::string str,sf::Vector2f position);
        std::vector<sf::Text> createCharacterNames(std::string str,sf::Vector2f position);
        std::vector<sf::Text> createPlayerName(std::string str,sf::Vector2f position);
        std::vector<sf::Text> createMessage(std::string str,sf::Vector2f position,std::string owner);
        std::vector<sf::Text> createDimensionalText(std::string text, std::string font, sf::Color color, float percentageFontSize, sf::Vector2f percentagePosition=sf::Vector2f(1,1), sf::Text::Style style=sf::Text::Style::Regular);
        std::vector<sf::Text> createTitle(std::string title,float percentageFontSize, sf::Vector2f percentagePosition);
    }
}

namespace TextModule
{
    sf::RectangleShape getBoundaryBox(sf::Text text,std::string font);
    sf::Vector2f getExactPos(sf::Text text,std::string font);
    sf::Vector2f getExactSize(sf::Text text,std::string font);
    bool isClicked(sf::Text text,std::string font,sf::Vector2i pos);
    void correctOffset(sf::Text &text, std::string font);
    void fitContainer(sf::Text &text, std::string font,sf::Vector2f containerPos, sf::Vector2f containerSize);
    void centerWidthOnly(sf::Text &text, std::string font, sf::Vector2f containerPos, sf::Vector2f containerSize);
    void centerHeightOnly(sf::Text &text, std::string font, sf::Vector2f containerPos, sf::Vector2f containerSize);
    void centerResolutionWidth(sf::Text &text, std::string font);
}

#endif  // TEXT_HPP
