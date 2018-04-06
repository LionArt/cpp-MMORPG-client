#include "Player.hpp"

Player::Player(std::string sname,sf::Vector2f pos,unsigned int dir,unsigned int animCounter)
{
    sprite.setTexture(ResourceHandler::loadTexture(PLAYER_FILE,"player"));
    sprite.setPosition(sf::Vector2f(218,50)+sf::Vector2f(32*pos.x,32*pos.y));
    sprite.setTextureRect(sf::IntRect((animCounter+1)*32,dir*32,32,32));
    direction=dir;
    animationCounter=animCounter;
}

void Player::update(sf::Vector2f pos,unsigned int dir,unsigned int animCounter)
{
    sprite.setPosition(pos);
    if(animCounter==2)
    {
        animCounter=0;
        animationCounter=animCounter;
    }
    sprite.setTextureRect(sf::IntRect((animCounter+1)*32,dir*32,32,32));
}
