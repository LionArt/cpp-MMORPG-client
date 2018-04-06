#ifndef DEFAULT_SETTINGS_HPP
#define DEFAULT_SETTINGS_HPP

#define IP_ADDRESS "7.72.174.164"
#define PORT 30000
#define HEARTBEAT_TIMEOUT 5000

#define MAP_WIDTH 29
#define MAP_HEIGHT 19

#define MENU_INFO_CHARACTER_SIZE 2.5
#define CHAT_CHARACTER_SIZE 1.3
#define CREDITS_INFO_CHARACTER_SIZE 3
#define CHARACTER_SELECT_CHAR_SIZE 2.5
#define CHARACTER_SELECT_BUTTON_CHAR_SIZE 1.5
#define MESSAGE_CHARACTER_SIZE 1.25
#define PLAYER_NAME_CHAR_SIZE 1.4
#define BUTTON_CHARACTER_SIZE 3
#define TEXTBOX_CHARACTER_SIZE 3.5
#define TITLE_CHARACTER_SIZE 14

#define MENU_BUTTON_MAX_CHARACTERS 7
#define MENU_TEXTBOX_MAX_CHARACTERS 20
#define DEFAULT_FONT "storybook"

#include "SFML/Graphics.hpp"

class VideoSettings
{
    public:
    static sf::VideoMode CurrentVideoMode;
};

class ButtonSettings
{
    public:
    static const sf::Color ButtonColor;
    static const sf::Vector2f MenuButtonSize;
    static const sf::Vector2f CharacterSelectButtonSize;
    static const sf::Color ButtonTextColor;
};

class TextSettings
{
    public:
    static const sf::Color TitleColor;
    static const sf::Color MenuInfoColor;
    static const sf::Color MenuGrayColor;
    static const sf::Color MenuErrorColor;
    static const sf::Color MessageColor;
};

class InterfaceSettings
{
    public:
    static const sf::Color InterfaceBodyColor;
    static const sf::Color CreditsInterfaceBodyColor;
    static const sf::Color InterfaceTitleBarColor;
    static const sf::Color InterfaceTitleTextColor;
};

class TextBoxSettings
{
    public:
    static const sf::Color TextBoxColor;
    static const sf::Vector2f TextBoxSize;
    static const sf::Vector2f ChatSize;
    static const sf::Color TextBoxTextColor;
    static const sf::Color ChatColor;
};
#endif // DEFAULT_SETTINGS_HPP
