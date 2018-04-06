#include "Application.hpp"

void Application::initializeBackground()
{
    background.setTexture(resourceHandler.loadTexture(BACKGROUND_FILE,"background"));
    background.setScale(VideoSettings::CurrentVideoMode.width/background.getLocalBounds().width,VideoSettings::CurrentVideoMode.height/background.getLocalBounds().height);
}

void Application::initializeAudio()
{
    bgm.openFromFile(MENU_BACKGROUND_MUSIC_FILE);
    bgm.setLoop(true);
    bgm.setVolume(100);
    bgm.play();
    sf::SoundBuffer click;
    click.loadFromFile(CLICK_EFFECT_FILE);
    soundBuffers.push_back(click);
    sound.setBuffer(soundBuffers[0]);
}
void Application::initializeIcon(sf::RenderWindow &window)
{
    icon.loadFromFile(ICON_FILE);
    window.setIcon(246,251,icon.getPixelsPtr());
}
void Application::initializeInterface()
{
    sf::CheckBox checkBox=sf::CheckBox(sf::Vector2f(56.4,53.1),2,ButtonSettings::ButtonColor,TextSettings::MenuInfoColor, sf::Color(50,50,50), true);
    sf::Interface Menu=GUI::Interface::createFullscreenInterface("Menu",false);
    //sf::Slider slider=sf::Slider(sf::Vector2f(43,80),sf::Vector2f(20,3), sf::Vector2f(5,140),ButtonSettings::ButtonColor,TextSettings::MenuInfoColor);
    //sf::Spinner spinner=sf::Spinner(sf::Vector2f(43,70),sf::Vector2f(20,3),ButtonSettings::ButtonColor,sf::Color::White,1,2,"Test",DEFAULT_FONT,3,sf::Color::White);
    //slider.centerResolutionWidth();
    //spinner.centerResolutionWidth();
    Menu.checkboxes.push_back(checkBox);
   // Menu.spinners.push_back(spinner);
    //Menu.sliders.push_back(slider);
    Menu.addButton(GUI::Button::createMenuButton("LOGIN",sf::Vector2f(43,55.5)));
    Menu.addButton(GUI::Button::createMenuButton("CREDITS",sf::Vector2f(2,89)));
    Menu.addButton(GUI::Button::createMenuButton("EXIT",sf::Vector2f(84,89)));
    Menu.addTextBox(GUI::TextBox::createLoginTextBox(sf::Vector2f(35,47),true));
    Menu.addTextBox(GUI::TextBox::createLoginTextBox(sf::Vector2f(35,39)));
    std::vector<sf::Text> text=GUI::Text::createMenuInfoText(CLIENT_VERSION ,sf::Vector2f(72,2));
    for(unsigned int i=0;i<text.size();i++)
    {
        text[i].setPosition(VideoSettings::CurrentVideoMode.width-(text[i].getGlobalBounds().width+10),text[i].getPosition().y);
        Menu.addText(text[i]);
    }
    sf::Text rem=GUI::Text::createDefaultText("Remember Login",DEFAULT_FONT,sf::Color::White,1.5,sf::Vector2f(35,53));
    TextModule::centerResolutionWidth(rem,DEFAULT_FONT);
    Menu.checkboxes[0].setPosition(sf::Vector2f(TextModule::getExactPos(rem,DEFAULT_FONT).x-Menu.checkboxes[0].getSize().x-6,Menu.checkboxes[0].getPosition().y-2.5));
    Menu.addText(rem);
    text=GUI::Text::createMenuInfoText("Login:",sf::Vector2f(35,36));
    for(unsigned int i=0;i<text.size();i++)
    {
        TextModule::centerResolutionWidth(text[i],DEFAULT_FONT);
        Menu.addText(text[i]);
    }
    text=GUI::Text::createMenuInfoText("Password:",sf::Vector2f(35,44));
    for(unsigned int i=0;i<text.size();i++)
    {
        TextModule::centerResolutionWidth(text[i],DEFAULT_FONT);
        Menu.addText(text[i]);
    }
    text=GUI::Text::createMenuInfoText(CLIENT_COPYRIGHT,sf::Vector2f(35,95));
    for(unsigned int i=0;i<text.size();i++)
    {
        TextModule::centerResolutionWidth(text[i],DEFAULT_FONT);
        Menu.addText(text[i]);
    }
    Menu.buttons[0].centerResolutionWidth();
    text=GUI::Text::createTitle(title,TITLE_CHARACTER_SIZE,sf::Vector2f(1,11));
    for(unsigned int i=0;i<text.size();i++)
    {
        Menu.addText(text[i]);
    }
    rem=GUI::Text::createDefaultText("",DEFAULT_FONT,TextSettings::MenuErrorColor,2.3,sf::Vector2f(35,62));
    Menu.addText(rem);
    interfaces.push_back(Menu);

}

void Application::initializeMenu()
{
    initializeBackground();
    initializeAudio();
    resourceHandler.loadFont(FONT_FILE_STORYBOOK,"storybook");
    resourceHandler.loadTexture(PLAYER_FILE,"player");
    initializeInterface();
    tileset=resourceHandler.loadTexture(TILESET_FILE,"tileset");
}

void Application::run()
{
    //if(!verifyFiles());
    //error message;
    //return 0;
    //else
    contextSettings.antialiasingLevel = 8;
    initializeMenu();
    window.create(VideoSettings::CurrentVideoMode, "Treasuria",sf::Style::Fullscreen,contextSettings);
    initializeIcon(window);
    std::thread packetTransfer(&NetworkHandler::sendAndReceivePackets,&networkHandler);
    sf::View gameView;
    gameView.setSize(VideoSettings::CurrentVideoMode.width,VideoSettings::CurrentVideoMode.height);
    gameView.zoom(0.5f);
    while (window.isOpen())
    {
        stateHandler.handleStates(state,sound,bgm,background,resourceHandler,window,interfaces,networkHandler);
        sf::Event event;
        while (window.pollEvent(event))
        {
            eventHandler.handleEvents(event,state,sound,window,interfaces,networkHandler);
        }
        //State handler utworzony jest poniewaz eventy przetwarzane sa tylko podczas jakiegokolwiek wydarzenia,
        //podczas zmian tylko w stanie gry, wydarzenia nie maja miejsca co sprawiloby, ze obiekty wymagajace aktualizacji
        //podczas braku wydarzen nie bylyby odpowiednio aktualizowane
        renderManager.draw(window,state,interfaces,background,tileset,gameView,networkHandler);
    }
    packetTransfer.detach();
}
