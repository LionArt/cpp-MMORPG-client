#ifndef CLIENT_MATH_HPP
#define CLIENT_MATH_HPP

#include <SFML/Graphics.hpp>
#include "DefaultSettings.hpp"

namespace clientMath
{
    sf::Vector2f scaleWithResolution(sf::Vector2f position,int modX=0, int modY=0);
    sf::Color calcColorChange(sf::Color,int r,int g,int b,int a=0);
    int scaleFontSize (int height,float p);
    void calcDimResolutionMod (int &shadowMod, int &lightMod);
}

#endif  // CLIENT_MATH_HPP
