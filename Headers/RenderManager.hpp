#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

#include "SFML/Graphics.hpp"
#include "NetworkHandler.hpp"
#include "GUI/Interface.hpp"

class RenderManager
{
    public:
    void draw(sf::RenderWindow &window,GameState &state,std::vector<sf::Interface> &interfaces,sf::Sprite background,sf::Texture &tileset,sf::View &gameView,NetworkHandler &networkHandler);
    bool ready=false;
};

#endif // RENDER_MANAGER_HPP
