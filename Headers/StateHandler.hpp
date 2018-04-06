#ifndef STATE_HANDLER_HPP
#define STATE_HANDLER_HPP

#include "SFML/Graphics.hpp"
#include "GUI/Interface.hpp"
#include "EventHandler.hpp"
#include "NetworkHandler.hpp"
#include "ResourceHandler.hpp"
#include "ResourceFiles.hpp"
#include "DefaultSettings.hpp"

class StateHandler
{
    public:
    void handleStates(GameState &state, sf::Sound &sound,sf::Music &music,sf::Sprite &background,ResourceHandler &ResourceHandler,sf::RenderWindow &window,std::vector<sf::Interface> &interfaces, NetworkHandler &networkHandler);
};

#endif // STATE_HANDLER_HPP
