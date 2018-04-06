#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "SFML/Graphics.hpp"
#include "DrawableObject.hpp"
#include "CheckBox.hpp"
#include "Button.hpp"
#include "TextBox.hpp"
#include "Slider.hpp"
#include "Spinner.hpp"

namespace sf
{
    class Interface: public DrawableObject
    {
        public:
        sf::Text text;
        sf::RectangleShape title;
        sf::RectangleShape bodyBorder;
        std::string textFont;
        std::vector <sf::Text> texts;
        std::vector <sf::CheckBox> checkboxes;
        std::vector <sf::Slider> sliders;
        std::vector <sf::Spinner> spinners;
        std::vector <sf::Button> buttons;
        std::vector <sf::TextBox> textboxes;
        std::vector <sf::Interface> interfaces;
        Interface(sf::Vector2f position,sf::Vector2f size, sf::Color color, sf::Color titleColor, std::string title,std::string font,float percentageFontSize, sf::Color textColor, sf::Text::Style style=sf::Text::Style::Regular);
        sf::Vector2f getPosition();
        std::string getTitle();
        void setTitle(std::string newString);
        void setPosition(sf::Vector2f pos);
        void centerResolutionWidth();
        void draw(sf::RenderWindow &window);
        void addButton(sf::Button button);
        void addTextBox(sf::TextBox textBox);
        void addText (sf::Text text);
    };
}

namespace GUI
{
    namespace Interface
    {
         sf::Interface createFullscreenInterface(std::string title, bool visible=true);
         sf::Interface createCreditsInterface(std::string title, bool visible=false);
         sf::Interface createCharacterSelect(std::string title, bool visible=false);
         sf::Interface createConnectionInterface(std::string title, bool visible=false);
    }
}
#endif // INTERFACE_HPP
