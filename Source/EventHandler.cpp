#include "EventHandler.hpp"

void EventHandler::handleEvents(sf::Event event, GameState &state, sf::Sound &sound,sf::RenderWindow &window, std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler)
{
    if(state==GameState::MENU)
    {
        if(event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left)
        {
            if(interfaces[0].buttons[2].isClicked(sf::Mouse::getPosition()))
            {
                sound.play();
                handleCloseEvent(window,interfaces,networkHandler);
            }
            else if(interfaces[0].textboxes[0].isClicked(sf::Mouse::getPosition()))
            {
                handleLoginActivateEvent(interfaces);
            }
            else if(interfaces[0].textboxes[1].isClicked(sf::Mouse::getPosition()))
            {
                handlePasswordActivateEvent(interfaces);
            }
            else if(interfaces[0].checkboxes[0].isClicked(sf::Mouse::getPosition()))
            {
                sound.play();
                handleRememberLoginEvent(interfaces);
            }
            else if(interfaces[0].buttons[1].isClicked(sf::Mouse::getPosition()))
            {
                sound.play();
                handleCreditsEvent(state,interfaces);
            }
            else if(interfaces[0].buttons[0].isClicked(sf::Mouse::getPosition()))
            {
                sound.play();
                handleLoginEvent(state,interfaces,networkHandler);
            }
        }
        if(event.type==sf::Event::TextEntered)
        {
            if((event.text.unicode>=48 && event.text.unicode<=57) ||
            (event.text.unicode>=65 && event.text.unicode<=90) ||
            (event.text.unicode>=97 && event.text.unicode<=122))
            {
                if(interfaces[0].textboxes[0].isActive())
                {
                    if(interfaces[0].textboxes[0].getText().length()<20)
                    handleAddLoginCharacterEvent(static_cast<char>(event.text.unicode), interfaces);
                }
                else if(interfaces[0].textboxes[1].isActive())
                {
                    if(interfaces[0].textboxes[1].getText().length()<20)
                    handleAddPasswordCharacterEvent(static_cast<char>(event.text.unicode), interfaces);
                }
            }
            if(event.text.unicode==8)
            {
                if(interfaces[0].textboxes[0].isActive())
                {
                    if(interfaces[0].textboxes[0].getText().length()>0)
                    handleDeleteLoginCharacterEvent(interfaces);
                }
                else if(interfaces[0].textboxes[1].isActive())
                {
                    if(interfaces[0].textboxes[1].getText().length()>0)
                    handleDeletePasswordCharacterEvent(interfaces);
                }
            }
            if(event.text.unicode==9)
            {
                if(interfaces[0].textboxes[0].isActive())
                handlePasswordActivateEvent(interfaces);
                else
                handleLoginActivateEvent(interfaces);
            }
            if(event.text.unicode==13)
            {
                if(interfaces[0].textboxes[0].isActive() || interfaces[0].textboxes[1].isActive())
                handleLoginEvent(state,interfaces,networkHandler);
            }
        }
    }
    else if(state==GameState::CREDITS)
    {
        if(((event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left) && (interfaces[1].buttons[0].isClicked(sf::Mouse::getPosition()))) ||((event.type==sf::Event::TextEntered) && (event.text.unicode==13)))
        {
                sound.play();
                handleMenuOkButtonEvent(state,interfaces);
        }
    }
    else if(state==GameState::CHARACTER_SELECT)
    {
        if(((event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left)&&(interfaces[1].buttons[0].isClicked(sf::Mouse::getPosition()))))
        {
            sound.play();
            handleConnectionCancelButtonEvent(state,interfaces,networkHandler);
        }
        else if(((event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left)&&(interfaces[1].buttons[1].isClicked(sf::Mouse::getPosition())))||((event.type==sf::Event::TextEntered) && (event.text.unicode==13)))
        {
            if(networkHandler.data.activeCharacter!=0)
            {
                sound.play();
                handleMenuOkButtonEvent(state,interfaces);
                handleCharacterChoice(state,interfaces,networkHandler);
            }
        }
        else
        for(unsigned int i=0;i<networkHandler.data.names.size();i++)
        {
            if((event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left)&&TextModule::isClicked(interfaces[1].texts[i*3],DEFAULT_FONT,sf::Mouse::getPosition()))
            {
                setCharacterNameActive(interfaces,networkHandler,i+1);
                break;
            }
        }
        if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Down)
        {
            if(networkHandler.data.activeCharacter<networkHandler.data.names.size())
            setCharacterNameActive(interfaces,networkHandler,networkHandler.data.activeCharacter+1);
        }
        if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Up)
        {
            if(networkHandler.data.activeCharacter>1)
            setCharacterNameActive(interfaces,networkHandler,networkHandler.data.activeCharacter-1);
        }
    }

    else if(state==GameState::CONNECTION_ERROR)
    {
        if(((event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left) && (interfaces[1].buttons[0].isClicked(sf::Mouse::getPosition()))) ||((event.type==sf::Event::TextEntered) && (event.text.unicode==13)))
        {
                sound.play();
                handleConnectionCancelButtonEvent(state,interfaces,networkHandler);
        }
    }
    else if(state==GameState::CONNECTING)
    {
        if(((event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left) && (interfaces[1].buttons[0].isClicked(sf::Mouse::getPosition()))) ||((event.type==sf::Event::TextEntered) && (event.text.unicode==13)))
        {
            sound.play();
            handleConnectionCancelButtonEvent(state,interfaces,networkHandler);
        }
    }
    else if(state==GameState::PLAYING)
    {
        if(event.type==sf::Event::KeyPressed)
        {
            if(event.key.code==sf::Keyboard::Down)
            {
                networkHandler.player.counter+=networkHandler.player.movementSpeed;
                if(networkHandler.player.direction!=0)
                {
                   networkHandler.player.direction=0;
                   networkHandler.player.counter=10.7;
                   networkHandler.player.animationCounter=-1;
                }
                else if(networkHandler.player.counter>=10.7)
                {
                    networkHandler.player.counter=0;
                    networkHandler.player.animationCounter++;
                }
                networkHandler.player.update(networkHandler.player.sprite.getPosition(),networkHandler.player.direction,networkHandler.player.animationCounter);
            }
            else if(event.key.code==sf::Keyboard::Up)
            {
                networkHandler.player.counter+=networkHandler.player.movementSpeed;
                if(networkHandler.player.direction!=1)
                {
                    networkHandler.player.counter=10.7;
                    networkHandler.player.direction=1;
                    networkHandler.player.animationCounter=-1;
                }
                else if(networkHandler.player.counter>=10.7)
                {
                    networkHandler.player.counter=0;
                    networkHandler.player.animationCounter++;
                }
                networkHandler.player.update(networkHandler.player.sprite.getPosition(),networkHandler.player.direction,networkHandler.player.animationCounter);
            }
            else if(event.key.code==sf::Keyboard::Left)
            {
                networkHandler.player.counter+=networkHandler.player.movementSpeed;
                if(networkHandler.player.direction!=3)
                {
                    networkHandler.player.counter=10.7;
                    networkHandler.player.direction=3;
                    networkHandler.player.animationCounter=-1;
                }
                else if(networkHandler.player.counter>=10.7)
                {
                    networkHandler.player.counter=0;
                    networkHandler.player.animationCounter++;
                }
                networkHandler.player.update(networkHandler.player.sprite.getPosition(),networkHandler.player.direction,networkHandler.player.animationCounter);
            }
            else if(event.key.code==sf::Keyboard::Right)
            {
                networkHandler.player.counter+=networkHandler.player.movementSpeed;
                if(networkHandler.player.direction!=2)
                {
                    networkHandler.player.counter=10.7;
                    networkHandler.player.direction=2;
                    networkHandler.player.animationCounter=-1;
                }
                else if(networkHandler.player.counter>=10.7)
                {
                    networkHandler.player.counter=0;
                    networkHandler.player.animationCounter++;
                }
                networkHandler.player.update(networkHandler.player.sprite.getPosition(),networkHandler.player.direction,networkHandler.player.animationCounter);
            }
            if(event.key.code==sf::Keyboard::Escape)
            {
                handleCloseEvent(window,interfaces,networkHandler);
            }
        }
        else if((event.type==sf::Event::TextEntered) && (event.text.unicode==13))
        {
            handleChatEvent(state,interfaces);
        }
        else
        {
            networkHandler.player.counter=10.7;
            networkHandler.player.animationCounter=-1;
            networkHandler.player.update(networkHandler.player.sprite.getPosition(),networkHandler.player.direction,networkHandler.player.animationCounter);
        }
    }
    else if(state==GameState::TYPING)
    {
        if(networkHandler.player.animationCounter!=-1)
        {
            networkHandler.player.counter=10.7;
            networkHandler.player.animationCounter=-1;
            networkHandler.player.update(networkHandler.player.sprite.getPosition(),networkHandler.player.direction,networkHandler.player.animationCounter);
        }
        if(event.type==sf::Event::TextEntered)
        {
            if(event.text.unicode==13)
            {
                handleSendMessageEvent(state,interfaces,networkHandler);
            }
            if(event.text.unicode>=32 && event.text.unicode<=126)
            {
                if(interfaces[0].textboxes[0].getText().length()<66)
                handleAddChatCharacterEvent(static_cast<char>(event.text.unicode), interfaces);
            }
            if(event.text.unicode==8)
            {
                if(interfaces[0].textboxes[0].getText().length()>0)
                handleDeleteChatCharacterEvent(interfaces);
            }
        }
    }
}

void EventHandler::handleChatEvent(GameState &state,std::vector<sf::Interface> &interfaces)
{
    state=GameState::TYPING;
    sf::Interface Chat=GUI::Interface::createFullscreenInterface("Chat",false);
    Chat.addTextBox(GUI::TextBox::createChatTextBox());
    interfaces.push_back(Chat);
}

void EventHandler::handleConnectionCancelButtonEvent(GameState &state, std::vector<sf::Interface> &interfaces, NetworkHandler &networkHandler)
{
    state=GameState::MENU;
    interfaces.pop_back();
    networkHandler.closeConnection();
}

void EventHandler::handleCloseEvent(sf::RenderWindow &window,std::vector<sf::Interface> &interfaces, NetworkHandler &networkHandler)
{
    networkHandler.terminateConnection();
    interfaces.clear();
    window.close();
}

void EventHandler::handleLoginActivateEvent(std::vector<sf::Interface> &interfaces)
{
    interfaces[0].textboxes[0].setActive(true);
    interfaces[0].textboxes[1].setActive(false);
}

void EventHandler::handlePasswordActivateEvent(std::vector<sf::Interface> &interfaces)
{
    interfaces[0].textboxes[0].setActive(false);
    interfaces[0].textboxes[1].setActive(true);
}

void EventHandler::handleRememberLoginEvent (std::vector<sf::Interface> &interfaces)
{
    if(interfaces[0].checkboxes[0].isActive())
    interfaces[0].checkboxes[0].setActive(false);
    else
    interfaces[0].checkboxes[0].setActive(true);
}

void EventHandler::handleAddLoginCharacterEvent(char c,std::vector<sf::Interface> &interfaces)
{
    interfaces[0].textboxes[0].setText(interfaces[0].textboxes[0].getTextValue()+c);
}

void EventHandler::handleAddChatCharacterEvent(char c,std::vector<sf::Interface> &interfaces)
{
    interfaces[0].textboxes[0].setText(interfaces[0].textboxes[0].getTextValue()+c);
}

void EventHandler::handleDeleteChatCharacterEvent(std::vector<sf::Interface> &interfaces)
{
    std::string s;
    s=interfaces[0].textboxes[0].getTextValue();
    s.erase(s.length()-1,1);
    interfaces[0].textboxes[0].setText(s);
}

void EventHandler::handleAddPasswordCharacterEvent(char c, std::vector<sf::Interface> &interfaces)
{
    interfaces[0].textboxes[1].setText(interfaces[0].textboxes[1].getTextValue()+c);
}

void EventHandler::handleDeleteLoginCharacterEvent(std::vector<sf::Interface> &interfaces)
{
    std::string s;
    s=interfaces[0].textboxes[0].getTextValue();
    s.erase(s.length()-1,1);
    interfaces[0].textboxes[0].setText(s);
}

void EventHandler::handleDeletePasswordCharacterEvent(std::vector<sf::Interface> &interfaces)
{
    std::string s;
    s=interfaces[0].textboxes[1].getTextValue();
    s.erase(s.length()-1,1);
    interfaces[0].textboxes[1].setText(s);
}

void EventHandler::handleCreditsEvent(GameState &state,std::vector<sf::Interface> &interfaces)
{
    state=GameState::CREDITS;
    sf::Interface Credits=GUI::Interface::createCreditsInterface("Credits",true);
    Credits.addButton(GUI::Button::createMenuButton("OK",sf::Vector2f(43,72)));
    std::vector<sf::Text> text=GUI::Text::createCreditsInfoText("Code, idea, development\nAndrulewicz Artur\n\nGame Background\nRandoMiss88 (DeviantArt)\n\nMenu background music\nThe Forest and the Trees by Kevin MacLeod\n\nGame background music\nCipher - Electronic Light by Kevin MacLeod\n\nSpecial thanks to everyone who supported me :)",sf::Vector2f(35,27));
    for(unsigned int i=0;i<text.size();i++)
    {
        TextModule::centerResolutionWidth(text[i],DEFAULT_FONT);
        Credits.addText(text[i]);
    }
    interfaces.push_back(Credits);
}

void EventHandler::handleCharacterSelect(GameState &state,std::vector<sf::Interface> &interfaces, NetworkHandler &networkHandler)
{
    state=GameState::CHARACTER_SELECT;
    sf::Interface CharacterSelect=GUI::Interface::createCharacterSelect("Character select",true);
    CharacterSelect.addButton(GUI::Button::createCharacterSelectButton("CANCEL",sf::Vector2f(50.5,63)));
    CharacterSelect.addButton(GUI::Button::createCharacterSelectButton("LOGIN",sf::Vector2f(41.5,63)));
    for(unsigned i=0;i<networkHandler.data.names.size();i++)
    {
        std::vector<sf::Text> text=GUI::Text::createCharacterNames(networkHandler.data.names[i],sf::Vector2f(35,30+(2.8*i)));
        for(unsigned int j=0;j<text.size();j++)
        {
            TextModule::centerResolutionWidth(text[j],DEFAULT_FONT);
            CharacterSelect.addText(text[j]);
        }
    }
    interfaces.push_back(CharacterSelect);
    setCharacterNameActive(interfaces,networkHandler,1);
}

void EventHandler::setCharacterNameActive(std::vector<sf::Interface> &interfaces, NetworkHandler &networkHandler, unsigned int id)
{
    if(networkHandler.data.names.size()>=id && id>0)
    {
        sf::Color color;
        clientMath::calcColorChange(color,TextSettings::MenuInfoColor.r,TextSettings::MenuInfoColor.g,TextSettings::MenuInfoColor.b);
        interfaces[1].texts[3*(id-1)].setColor(color);
        interfaces[1].texts[3*(id-1)+1].setColor(sf::Color::Black);
        interfaces[1].texts[3*(id-1)+2].setColor(TextSettings::MenuInfoColor);
        clientMath::calcColorChange(color,255,255,255);
        if((networkHandler.data.activeCharacter!=0 && id!=networkHandler.data.activeCharacter)&&networkHandler.data.activeCharacter<=networkHandler.data.names.size())
        {
            interfaces[1].texts[3*(networkHandler.data.activeCharacter-1)].setColor(color);
            interfaces[1].texts[3*(networkHandler.data.activeCharacter-1)+2].setColor(sf::Color::White);
        }
        networkHandler.data.activeCharacter=id;
    }
    else
    networkHandler.data.activeCharacter=0;
}

void EventHandler::handleMenuOkButtonEvent(GameState &state,std::vector<sf::Interface> &interfaces)
{
    state=GameState::MENU;
    interfaces.pop_back();
}

void EventHandler::handleSendMessageEvent(GameState &state,std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler)
{
    state=GameState::PLAYING;
    if(interfaces[0].textboxes[0].getText().length()>0)
    {
        networkHandler.newMessage=interfaces[0].textboxes[0].getText();
        networkHandler.sendMessage=true;
    }
    interfaces.pop_back();
}

void EventHandler::handleLoginPasswordValidation(std::string login,std::string password,std::vector<sf::Interface> &interfaces)
{
        std::string text="";
        if(login.length()==0 && password.length()==0)
        {
            text="Password and login are required.";
        }
        else if(login.length()==0)
        {
            text="Login is required.";
        }
        else if(password.length()==0)
        {
            text="Password is required.";
        }
        else if(login.length()<4 && password.length()<4)
        {
            text="Password and login are too short. They should have at least 4 characters.";
        }
        else if(login.length()<4)
        {
            text="Login is too short. It should have at least 6 characters.";
        }
        else
        {
            text="Password is too short. It should have at least 6 characters.";
        }
        interfaces[0].texts[interfaces[0].texts.size()-1].setString(text);
        TextModule::centerResolutionWidth(interfaces[0].texts[interfaces[0].texts.size()-1],DEFAULT_FONT);
}

void EventHandler::handleConnectionError(GameState &state, std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler)
{
    state=GameState::CONNECTION_ERROR;
    std::string title="Connection Failed";
    std::string text="Problems with connecting to the server. Check your connection.";
    if(networkHandler.connectionError==ConnectionError::DENIED)
    title="Connection Denied";
    if(networkHandler.connectionError==ConnectionError::TIMEOUT)
    title="Connection Timeout";
    if(networkHandler.connectionError==ConnectionError::WRONG_DATA || networkHandler.connectionError==ConnectionError::ACCOUNT_LOGGED || networkHandler.connectionError==ConnectionError::CHARACTER_LOGGED)
    title="Login Error";
    sf::Interface connectionError=GUI::Interface::createConnectionInterface(title,true);
    connectionError.addButton(GUI::Button::createMenuButton("OK",sf::Vector2f(43,50)));
    if(networkHandler.connectionError==ConnectionError::DENIED)
    text="Connection from the server has been denied.";
    if(networkHandler.connectionError==ConnectionError::TIMEOUT)
    text="Cannot connect to login server. Connection timed out. ";
    if(networkHandler.connectionError==ConnectionError::WRONG_DATA)
    text="Please enter valid login and password. ";
    if(networkHandler.connectionError==ConnectionError::ACCOUNT_LOGGED)
    text="Someone is already logged on this account.";
    if(networkHandler.connectionError==ConnectionError::CHARACTER_LOGGED)
    text="Your character is already logged in.";
    std::vector<sf::Text> err=GUI::Text::createCreditsInfoText(text,sf::Vector2f(35,44));
    for(unsigned int i=0;i<err.size();i++)
    {
        TextModule::centerResolutionWidth(err[i],DEFAULT_FONT);
        connectionError.addText(err[i]);
    }
    interfaces.push_back(connectionError);
    networkHandler.connectionState=ConnectionState::DISCONNECTED;
    networkHandler.connectionError=ConnectionError::DEFAULT;
}

void EventHandler::handleConnectionSuccess(GameState &state, std::vector<sf::Interface> &interfaces,
NetworkHandler &networkHandler)
{
    state=GameState::CONNECTING;
    networkHandler.connectionState=ConnectionState::CONNECTED;
    sf::Interface connection=GUI::Interface::createConnectionInterface("Connection Status",true);
    connection.addButton(GUI::Button::createMenuButton("Cancel",sf::Vector2f(43,50)));
    std::vector<sf::Text> text=GUI::Text::createCreditsInfoText("Connecting...",sf::Vector2f(35,44));
    for(unsigned int i=0;i<text.size();i++)
    {
        TextModule::centerResolutionWidth(text[i],DEFAULT_FONT);
        connection.addText(text[i]);
    }
    interfaces.push_back(connection);
}

void EventHandler::handleCharacterChoice(GameState &state, std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler)
{
    state=GameState::CONNECTING;
    networkHandler.connectionState=ConnectionState::CHARACTER_SELECTED;
    sf::Interface connection=GUI::Interface::createConnectionInterface("Connection Status",true);
    connection.addButton(GUI::Button::createMenuButton("Cancel",sf::Vector2f(43,50)));
    std::vector<sf::Text> text=GUI::Text::createCreditsInfoText("Connecting to the game world...",sf::Vector2f(35,44));
    for(unsigned int i=0;i<text.size();i++)
    {
        TextModule::centerResolutionWidth(text[i],DEFAULT_FONT);
        connection.addText(text[i]);
    }
    interfaces.push_back(connection);
}

void EventHandler::handleWorldCreation(GameState &state, sf::Music &music,sf::Sprite &background, ResourceHandler &resourceHandler,std::vector<sf::Interface> &interfaces,NetworkHandler &networkHandler)
{
    music.stop();
    music.openFromFile(GAME_BACKGROUND_MUSIC_FILE);
    music.play();
    sf::Sprite bg;
    bg.setTexture(resourceHandler.loadTexture(TEXTURE_FILE,"texture"));
    bg.setScale(VideoSettings::CurrentVideoMode.width/bg.getLocalBounds().width,VideoSettings::CurrentVideoMode.height/bg.getLocalBounds().height);
    background=bg;
    state=GameState::PLAYING;
    interfaces.pop_back();
}

void EventHandler::handleLoginEvent(GameState &state, std::vector<sf::Interface> &interfaces, NetworkHandler &networkHandler)
{
    interfaces[0].texts[interfaces[0].texts.size()-1].setString("");
    std::string password=interfaces[0].textboxes[0].getTextValue();
    std::string login=interfaces[0].textboxes[1].getTextValue();
    if(login.length()<4 || password.length()<4)
    handleLoginPasswordValidation(login,password,interfaces);
    else
    {
        if(networkHandler.socket.Disconnected)
        {
            if(!networkHandler.establishConnection(IP_ADDRESS,PORT))
            handleConnectionError(state,interfaces,networkHandler);
            else
            {
                networkHandler.data.login=login;
                networkHandler.data.password=password;
                handleConnectionSuccess(state,interfaces,networkHandler);
            }
        }
    }
}
