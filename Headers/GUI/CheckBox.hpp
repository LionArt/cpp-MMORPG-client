#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "SFML/Graphics.hpp"
#include "DrawableObject.hpp"
#include "ClientMath.hpp"

namespace sf
{
    class CheckBox: public DrawableObject
    {
        private:
        sf::RectangleShape body;
        sf::RectangleShape mark;
        sf::Color markColor;
        sf::Color inactiveColor;
        bool active;
        public:
        CheckBox(sf::Vector2f position,float size, sf::Color color, sf::Color markColor, sf::Color inactiveColor, bool isActive=false);
        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        bool isActive();
        bool isClicked(sf::Vector2i pos);
        void setActive(bool var);
        void setPosition(sf::Vector2f pos);
        void draw(sf::RenderWindow &window);
    };
}
#endif // CHECKBOX_HPP
