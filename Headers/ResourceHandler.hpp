#ifndef RESOURCE_HANDLER_HPP
#define RESOURCE_HANDLER_HPP

#include <iostream>
#include "SFML/Graphics.hpp"
#include "ResourceContainers.hpp"

class ResourceHandler
{
    public:
    static sf::Font &loadFont(std::string file,std::string name);
    static sf::Texture &loadTexture(std::string file,std::string name);
};

#endif // RESOURCE_HANDLER_HPP
