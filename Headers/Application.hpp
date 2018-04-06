#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <time.h>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "NetworkHandler.hpp"
#include "StateHandler.hpp"
#include "ResourceHandler.hpp"
#include "RenderManager.hpp"
#include "EventHandler.hpp"
#include "GUI/Interface.hpp"
#include "ResourceFiles.hpp"
#include "Player.hpp"
#include "Version.hpp"

class Application
{
    private:
    NetworkHandler networkHandler;
    RenderManager renderManager;
    StateHandler stateHandler;
    ResourceHandler resourceHandler;
    EventHandler eventHandler;
    GameState state=GameState::MENU;
    sf::Sound sound;
    sf::Music bgm;
    sf::RenderWindow window;
    sf::ContextSettings contextSettings;
    sf::Sprite background;
    sf::Image icon;
    sf::Texture tileset;
    std::string title="Treasuria";
    std::vector<sf::Interface> interfaces;
    std::vector<sf::SoundBuffer> soundBuffers;
    void initializeMenu();
    void initializeInterface();
    void initializeAudio();
    void initializeIcon(sf::RenderWindow &window);
    void initializeBackground();

    public:
    void run();

};

#endif //APPLICATION_HPP
