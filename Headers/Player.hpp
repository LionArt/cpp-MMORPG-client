#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SFML/Graphics.hpp"
#include "ResourceFiles.hpp"
#include "ResourceHandler.hpp"
#include "GUI/Text.hpp"

class Player
{
    public:
    Player(std::string sname,sf::Vector2f pos,unsigned int dir, unsigned int animCounter);
    unsigned int direction=2;
    float movementSpeed=1;
    float counter=10.7;
    int animationCounter=-1;
    sf::Sprite sprite;
    std::vector<sf::Text> name;
    void update(sf::Vector2f pos,unsigned int dir, unsigned int animCounter);
};

#endif // PLAYER_HPP
