#include "NetworkHandler.hpp"

bool NetworkHandler::establishConnection(sf::IpAddress ip,int port)
{
    socket.setBlocking(true);
    sf::Socket::Status status=socket.connect(ip,port);
    if(status!=sf::Socket::Done)
    {
        return false;
    }
    else
    {
        socket.setBlocking(false);
        connectionState=ConnectionState::CONNECTED;
        heartbeat.restart();
        return true;
    }
}

bool NetworkHandler::isConnected()
{
    if(socket.getRemoteAddress()==sf::IpAddress::None)
    return false;
    else
    return true;
}

void NetworkHandler::setConnectionState(ConnectionState state)
{
    connectionState=state;
}

void NetworkHandler::closeConnection()
{
    connectionState=ConnectionState::DISCONNECTED;
    socket.disconnect();
}

void NetworkHandler::terminateConnection()
{
    connectionState=ConnectionState::TERMINATED;
}

bool NetworkHandler::sendPacket(sf::Packet packet)
{
    if(socket.send(packet)==sf::Socket::Done)
    return true;
    else
    return false;
}


bool NetworkHandler::receivePacket(sf::Packet &packet)
{
    if(socket.receive(packet)==sf::Socket::Done)
    return true;
    else
    return false;
}


sf::Packet NetworkHandler::serialize(PacketHeader header)
{
    sf::Packet packet;
    packet<<static_cast<uint8_t>(header);
    switch(header)
    {
        case PacketHeader::HEARTBEAT:
        {
            break;
        }
        case PacketHeader::HANDSHAKE:
        {
            std::string version=CLIENT_VERSION;
            packet<<version;
            break;
        }
        case PacketHeader::LOGIN:
        {
            packet<<data.login<<data.password;
            break;
        }
        case PacketHeader::DISCONNECT:
        {
            break;
        }
        case PacketHeader::CHARACTER_SELECT:
        {
            packet<<static_cast<uint8_t>(data.activeCharacter);
            break;
        }
        case PacketHeader::PLAYER_MOVE:
        {
            packet<<static_cast<uint8_t>(player.direction)<<static_cast<int8_t>(player.animationCounter);
            break;
        }
        case PacketHeader::MESSAGE:
        {
            if(sendMessage)
            {
                packet<<newMessage;
                newMessage="";
                sendMessage=false;
            }
            break;
        }
        default:
        break;
    }
    return packet;
}

void NetworkHandler::deserialize(sf::Packet &packet)
{
    uint8_t _packetHeader;
    if(packet>>_packetHeader)
    {
        PacketHeader packetHeader=static_cast<PacketHeader>(_packetHeader);
        switch(packetHeader)
        {
            case PacketHeader::HEARTBEAT:
            {
                restartTimer();
                break;
            }
            case PacketHeader::HANDSHAKE:
            {
                if(connectionState==ConnectionState::CONNECTED)
                connectionState=ConnectionState::HANDSHAKED;
                break;
            }
            case PacketHeader::LOGIN:
            {
                if(connectionState==ConnectionState::HANDSHAKED)
                {
                    if(packet>>data.response)
                    {
                        data.names.clear();
                        for(unsigned int i=0;i<data.response;i++)
                        {
                            std::string name;
                            packet>>name;
                            data.names.push_back(name);
                        }
                        connectionState=ConnectionState::LOGGED;
                    }
                }
                break;
            }
            case PacketHeader::DISCONNECT:
            {
                uint8_t response;
                connectionState=ConnectionState::ERROR;
                if(packet>>response)
                connectionError=static_cast<ConnectionError>(response);
                break;
            }
            case PacketHeader::GAME:
            {
                uint16_t tile;
                for(unsigned int i=0;i<MAP_HEIGHT;i++)
                for(unsigned int j=0;j<MAP_WIDTH;j++)
                {
                    packet>>tile;
                    world[i][j]=static_cast<unsigned int>(tile);
                }
                for(unsigned int i=0;i<MAP_HEIGHT;i++)
                for(unsigned int j=MAP_WIDTH;j<MAP_WIDTH*2;j++)
                {
                    packet>>tile;
                    world[i][j]=static_cast<unsigned int>(tile);
                }
                uint16_t playerSize;
                packet>>playerSize;
                int pSize=static_cast<int>(playerSize);
                std::vector<Player> _players;
                players.empty();
                for(int i=0;i<pSize;i++)
                {
                    std::string name;
                    sf::Vector2f pos;
                    uint8_t dir;
                    int8_t animCounter;
                    packet>>name>>pos.x>>pos.y>>dir>>animCounter;
                    Player p(name,pos,static_cast<unsigned int>(dir),static_cast<int>(animCounter));
                    p.name=GUI::Text::createPlayerName(name,sf::Vector2f(0,0));
                    for(unsigned int i=0;i<player.name.size();i++)
                    {
                        TextModule::fitContainer(p.name[i],DEFAULT_FONT,p.sprite.getPosition(),sf::Vector2f(p.sprite.getTextureRect().width,p.sprite.getTextureRect().height));
                        p.name[i].setPosition(p.name[i].getPosition()-sf::Vector2f(0,21));
                    }
                    _players.push_back(p);
                }
                players=_players;
                player.sprite.setPosition(sf::Vector2f(218,50)+sf::Vector2f(32*14,32*9));
                uint16_t messageSize;
                packet>>messageSize;
                int mSize=static_cast<int>(messageSize);
                std::vector<sf::Text> _messages;
                messages.empty();
                for(int i=0;i<mSize;i++)
                {
                    std::string data;
                    sf::Vector2f pos;
                    std::string owner;
                    packet>>data>>pos.x>>pos.y>>owner;
                    std::vector<sf::Text> text;
                    pos=sf::Vector2f(218,50)+sf::Vector2f(32*pos.x,32*pos.y);
                    text=GUI::Text::createMessage(data,pos,owner);
                    for(int j=0;j<text.size();j++)
                    {
                        TextModule::fitContainer(text[j],DEFAULT_FONT,pos,sf::Vector2f(32,32));
                        text[j].setPosition(text[j].getPosition()-sf::Vector2f(0,30));
                        _messages.push_back(text[j]);
                    }
                }
                messages=_messages;
                if(connectionState!=ConnectionState::LOGIN_CONFIRMED)
                {
                    player.name=GUI::Text::createPlayerName(data.names[data.activeCharacter-1],sf::Vector2f(0,0));
                    for(unsigned int i=0;i<player.name.size();i++)
                    {
                        TextModule::fitContainer(player.name[i],DEFAULT_FONT,player.sprite.getPosition(),sf::Vector2f(player.sprite.getTextureRect().width,player.sprite.getTextureRect().height));
                        player.name[i].setPosition(player.name[i].getPosition()-sf::Vector2f(0,21));
                    }
                }
                connectionState=ConnectionState::LOGIN_CONFIRMED;
                break;
            }
            default:
            break;
        }
    }
}

int32_t NetworkHandler::getLastHearbeat()
{
    return heartbeat.getElapsedTime().asMilliseconds();
}

void NetworkHandler::restartTimer()
{
    heartbeat.restart();
}

void NetworkHandler::sendAndReceivePackets()
{
    while(connectionState!=ConnectionState::TERMINATED)
    {
        m_mutex.lock();
        if(connectionState!=ConnectionState::ERROR && connectionState!=ConnectionState::DISCONNECTED)
        {
            if(getLastHearbeat()<HEARTBEAT_TIMEOUT)
            {
                sendPacket(serialize(PacketHeader::HEARTBEAT));
                sf::Packet received;
                if(receivePacket(received))
                deserialize(received);
                if(connectionState==ConnectionState::CONNECTED)
                {
                    sendPacket(serialize(PacketHeader::HANDSHAKE));
                }
                else if(connectionState==ConnectionState::HANDSHAKED)
                {
                    sendPacket(serialize(PacketHeader::LOGIN));
                }
                else if(connectionState==ConnectionState::CHARACTER_SELECTED)
                {
                    sendPacket(serialize(PacketHeader::CHARACTER_SELECT));
                }
                else if(connectionState==ConnectionState::LOGIN_CONFIRMED)
                {
                    sendPacket(serialize(PacketHeader::PLAYER_MOVE));
                    sendPacket(serialize(PacketHeader::MESSAGE));
                }
            }
            else
            {
                players.empty();
                connectionState=ConnectionState::ERROR;
                connectionError=ConnectionError::TIMEOUT;
            }
        }
        m_mutex.unlock();
    }
}

NetworkHandler::NetworkHandler()
{
    connectionState=ConnectionState::DISCONNECTED;
}
