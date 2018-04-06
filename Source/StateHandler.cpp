#include "StateHandler.hpp"

void StateHandler::handleStates(GameState &state, sf::Sound &sound, sf::Music &music, sf::Sprite &background, ResourceHandler &resourceHandler,sf::RenderWindow &window, std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler)
{
    if(state==GameState::CONNECTING)
    {
        if(!networkHandler.isConnected() || networkHandler.connectionState==ConnectionState::ERROR)
        {
            EventHandler::handleMenuOkButtonEvent(state,interfaces);
            EventHandler::handleConnectionError(state,interfaces,networkHandler);
        }

        else if(networkHandler.connectionState==ConnectionState::LOGGED)
        {
            EventHandler::handleMenuOkButtonEvent(state,interfaces);
            EventHandler::handleCharacterSelect(state,interfaces,networkHandler);
        }
        else if(networkHandler.connectionState==ConnectionState::LOGIN_CONFIRMED)
        {
            EventHandler::handleMenuOkButtonEvent(state,interfaces);
            EventHandler::handleWorldCreation(state,music,background,resourceHandler,interfaces,networkHandler);
        }
    }
}
