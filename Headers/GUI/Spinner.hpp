#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include "SFML/Graphics.hpp"
#include "DrawableObject.hpp"
#include "ClientMath.hpp"
#include "GUI/Text.hpp"

namespace sf
{
    class Spinner: public DrawableObject
    {
        private:
        sf::Text text;
        sf::RectangleShape body;
        sf::RectangleShape leftButton;
        sf::RectangleShape rightButton;
        sf::CircleShape leftIcon;
        sf::CircleShape rightIcon;
        std::string font;
        unsigned int value;
        unsigned int maxValue;
        public:
        Spinner(sf::Vector2f position,sf::Vector2f size, sf::Color color,sf::Color buttonColor, unsigned int var, unsigned int maxVar,std::string title,std::string f,float percentageFontSize, sf::Color textColor, sf::Text::Style style=sf::Text::Style::Regular);
        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        unsigned int getValue();
        void setValue(unsigned int var);
        void setPosition(sf::Vector2f pos);
        void centerResolutionWidth();
        void draw(sf::RenderWindow &window);
    };
}
#endif // SELECTOR_HPP
