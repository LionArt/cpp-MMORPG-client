#ifndef RESOURCE_CONTAINERS_HPP
#define RESOURCE_CONTAINERS_HPP

#include <map>
#include "SFML/Graphics.hpp"

class ResourceContainers
{
    public:
    static std::map <std::string,sf::Font> fonts;
    static std::map <std::string,sf::Texture> textures;
};

#endif // RESOURCE_CONTAINERS_HPP
