#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "SFML/Graphics.hpp"
#include "GUI/Interface.hpp"
#include "NetworkHandler.hpp"
#include "ResourceHandler.hpp"
#include "ResourceFiles.hpp"
#include "Player.hpp"
#include "iostream"

class EventHandler
{
    friend class StateHandler;
    public:
    void handleEvents(sf::Event event,GameState &state, sf::Sound &sound,sf::RenderWindow &window,std::vector<sf::Interface> &interfaces, NetworkHandler &networkHandler);
    private:
    static void setCharacterNameActive(std::vector<sf::Interface> &interfaces, NetworkHandler &networkHandler, unsigned int id);
    void handleCloseEvent(sf::RenderWindow &window, std::vector<sf::Interface> &interfaces, NetworkHandler &networkHandler);
    void handleLoginActivateEvent(std::vector<sf::Interface> &interfaces);
    void handleChatEvent(GameState &state,std::vector<sf::Interface> &interfaces);
    void handlePasswordActivateEvent(std::vector<sf::Interface> &interfaces);
    void handleRememberLoginEvent (std::vector<sf::Interface> &interfaces);
    void handleSendMessageEvent(GameState &state,std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler);
    void handleAddLoginCharacterEvent(char c, std::vector<sf::Interface> &interfaces);
    void handleAddPasswordCharacterEvent(char c, std::vector<sf::Interface> &interfaces);
    void handleDeleteLoginCharacterEvent(std::vector<sf::Interface> &interfaces);
    void handleDeletePasswordCharacterEvent(std::vector<sf::Interface> &interfaces);
    void handleCreditsEvent (GameState &state,std::vector<sf::Interface> &interfaces);
    void handleAddChatCharacterEvent(char c,std::vector<sf::Interface> &interfaces);
    void handleDeleteChatCharacterEvent(std::vector<sf::Interface> &interfaces);
    static void handleCharacterSelect(GameState &state,std::vector<sf::Interface> &interfaces, NetworkHandler &networkHandler);
    static void handleMenuOkButtonEvent(GameState &state,std::vector<sf::Interface> &interfaces);
    void handleLoginEvent(GameState &state, std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler);
    void handleConnectionCancelButtonEvent(GameState &state, std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler);
    void handleLoginPasswordValidation(std::string login,std::string password,std::vector<sf::Interface> &interfaces);
    static void handleConnectionError(GameState &state, std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler);
    void handleConnectionSuccess(GameState &state, std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler);
    void handleCharacterChoice(GameState &state,std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler);
    static void handleWorldCreation(GameState &state,sf::Music &music,sf::Sprite &background, ResourceHandler &resourceHandler,std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler);
};

#endif // EVENT_HANDLER_HPP
