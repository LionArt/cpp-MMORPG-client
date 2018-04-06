#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "SFML/Graphics.hpp"
#include "DrawableObject.hpp"
#include "ClientMath.hpp"
#include <iostream>

namespace sf
{
    class Slider: public DrawableObject
    {
        private:
        sf::RectangleShape bar;
        sf::RectangleShape indicator;
        sf::Color indicatorColor;
        float value;
        float maxValue;
        float minValue;
        public:
        Slider(sf::Vector2f position,sf::Vector2f size, sf::Vector2f indicatorSize, sf::Color color, sf::Color indicatorColor, float var=50, float maxVar=100, float minVar=0, bool autosize=false);
        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        float getValue();
        void setValue(float var);
        void setPosition(sf::Vector2f pos);
        void centerResolutionWidth();
        void draw(sf::RenderWindow &window);
    };
}
#endif // SLIDER_HPP
