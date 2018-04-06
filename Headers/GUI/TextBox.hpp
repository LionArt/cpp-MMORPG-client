#ifndef TEXTBOX_HPP
#define TEXBOX_HPP

#include "SFML/Graphics.hpp"
#include "DrawableObject.hpp"
#include "ClientMath.hpp"
#include "Text.hpp"
#include <time.h>

namespace sf
{
    class TextBox: public DrawableObject
    {
        private:
        sf::RectangleShape body;
        sf::RectangleShape cursor;
        sf::Text text;
        std::string font;
        std::string textValue;
        bool active;
        bool encrypted;
        public:
        TextBox(sf::Vector2f position,sf::Vector2f size, sf::Color color,std::string f,float percentageFontSize, sf::Color textColor, sf::Text::Style style=sf::Text::Style::Regular, bool isActive=false, bool isEncrypted=false);
        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        std::string getText();
        std::string getTextValue();
        bool isActive();
        bool isClicked(sf::Vector2i pos);
        void setActive(bool var);
        void setText(std::string newString);
        void setTextValue(std::string newString);
        void setPosition(sf::Vector2f pos);
        void centerResolutionWidth();
        void setTextColor(sf::Color color);
        void draw(sf::RenderWindow &window);
    };
}

namespace GUI
{
    namespace TextBox
    {
        sf::TextBox createLoginTextBox(sf::Vector2f position, bool isEncrypted=false);
        sf::TextBox createChatTextBox();
    }
}

#endif // TEXTBOX_HPP
