#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "DrawableObject.hpp"
#include "Text.hpp"

namespace sf
{
    class Button: public DrawableObject
    {
        private:
        sf::Text text;
        sf::RectangleShape body;
        std::string textFont;
        public:
        Button(sf::Vector2f position,sf::Vector2f size, sf::Color color,std::string title,std::string f,float percentageFontSize, sf::Color textColor, sf::Text::Style style=sf::Text::Style::Regular);
        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        std::string getTitle();
        bool isClicked(sf::Vector2i pos);
        void setTitle(std::string newString);
        void setPosition(sf::Vector2f pos);
        void centerResolutionWidth();
        void setTextColor(sf::Color color);
        void draw(sf::RenderWindow &window);
    };
}

namespace GUI
{
    namespace Button
    {
        sf::Button createMenuButton(std::string title, sf::Vector2f position);
        sf::Button createCharacterSelectButton(std::string title, sf::Vector2f position);
    }
}

#endif // BUTTON_HPP
