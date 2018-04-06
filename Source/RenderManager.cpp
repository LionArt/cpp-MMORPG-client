#include "RenderManager.hpp"

void RenderManager::draw(sf::RenderWindow &window,GameState &state,std::vector<sf::Interface> &interfaces,sf::Sprite background, sf::Texture &tileset, sf::View &gameView, NetworkHandler &networkHandler)
{
    window.clear();
    window.draw(background);
    if(state==GameState::PLAYING || state==GameState::TYPING)
    {
        sf::RectangleShape game;
        game.setFillColor(sf::Color::Black);
        game.setSize(sf::Vector2f(928,608));
        game.setPosition(sf::Vector2f(0,50));
        game.setPosition(sf::Vector2f((round(game.getPosition().x+((0+((float(VideoSettings::CurrentVideoMode.width))/2))-game.getPosition().x-(float(game.getSize().x)/2))))-1,game.getPosition().y));
        game.setOutlineColor(sf::Color::Blue);
        game.setOutlineThickness(1);
        gameView.setCenter(networkHandler.player.sprite.getPosition()+sf::Vector2f(32,32));
        window.setView(gameView);
        window.draw(game);
        sf::Sprite tile;
        tile.setTexture(tileset);
        for(unsigned int i=0;i<MAP_HEIGHT;i++)
        for(unsigned int j=0;j<MAP_WIDTH;j++)
        {
            if(networkHandler.world[i][j]!=0)
            {
                tile.setPosition(game.getPosition()+sf::Vector2f(j*32,i*32));
                tile.setTextureRect(sf::IntRect((networkHandler.world[i][j]%32)*32-32, (networkHandler.world[i][j]/32)*32, 32, 32));
                window.draw(tile);
            }
        }
        for(unsigned int i=0;i<MAP_HEIGHT;i++)
        for(unsigned int j=MAP_WIDTH;j<MAP_WIDTH*2;j++)
        {
            if(networkHandler.world[i][j]!=0)
            {
                tile.setPosition(game.getPosition()+sf::Vector2f((j-MAP_WIDTH)*32,i*32));
                tile.setTextureRect(sf::IntRect((networkHandler.world[i][j]%32)*32-32, (networkHandler.world[i][j]/32)*32, 32, 32));
                window.draw(tile);
            }
        }
        for(unsigned int i=0;i<networkHandler.players.size();i++)
        {
            networkHandler.players[i].update(networkHandler.players[i].sprite.getPosition(),networkHandler.players[i].direction,networkHandler.players[i].animationCounter);
            window.draw(networkHandler.players[i].sprite);
            for(unsigned int j=0;j<networkHandler.players[i].name.size();j++)
            window.draw(networkHandler.players[i].name[j]);
        }
        window.draw(networkHandler.player.sprite);
        for(unsigned int i=0;i<networkHandler.player.name.size();i++)
        window.draw(networkHandler.player.name[i]);
        for(unsigned int i=0;i<networkHandler.messages.size();i++)
        {
            window.draw(networkHandler.messages[i]);
        }
    }
    for(unsigned i=0;i<interfaces.size();i++)
    interfaces[i].draw(window);
    window.display();
}
