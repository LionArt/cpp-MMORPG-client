#include "ResourceHandler.hpp"

sf::Texture& ResourceHandler::loadTexture(std::string f, std::string n)
{
    if(ResourceContainers::textures.find(n)==ResourceContainers::textures.end())
    {
        sf::Texture texture;
        if(!texture.loadFromFile(f))
        {
            std::cout<<"Couldn't load texture from "<<f<<" file."<<std::endl;
            return texture;
        }
        else
        {
            if (n.find("repeated") != std::string::npos)
            texture.setRepeated(true);
            ResourceContainers::textures[n]=texture;
            return ResourceContainers::textures[n];
        }
    }
    else
    return ResourceContainers::textures[n];
}

sf::Font& ResourceHandler::loadFont(std::string f, std::string n)
{
    if(ResourceContainers::fonts.find(n)==ResourceContainers::fonts.end())
    {
        sf::Font font;
        if(!font.loadFromFile(f))
        {
            std::cout<<"Couldn't load font from "<<f<<" file."<<std::endl;
            return font;
        }
        else
        {
            ResourceContainers::fonts[n]=font;
            return ResourceContainers::fonts[n];
        }
    }
    else
    return ResourceContainers::fonts[n];
}
