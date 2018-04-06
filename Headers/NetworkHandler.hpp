#ifndef NETWORK_HANDLER_HPP
#define NETWORK_HANDLER_HPP

#include "SFML/Network.hpp"
#include <thread>
#include <mutex>
#include <iostream>
#include "DefaultSettings.hpp"
#include "GUI/Text.hpp"
#include "PacketData.hpp"
#include "Player.hpp"
#include "Version.hpp"

enum class GameState{MENU,CREDITS,CONNECTION_ERROR,CONNECTING,CHARACTER_SELECT,PLAYING,TYPING};

class NetworkHandler
{
    public:
    std::mutex m_mutex;
    PacketData data;
    bool sendMessage=false;
    unsigned int world[MAP_HEIGHT][MAP_WIDTH*2];
    Player player=Player("Player",sf::Vector2f(0,0),0,-1);
    std::vector<sf::Text> messages;
    std::vector<Player> players;
    std::string newMessage="";
    NetworkHandler();
    sf::TcpSocket socket;
    ConnectionState connectionState;
    ConnectionError connectionError;
    sf::Clock heartbeat;
    int32_t getLastHearbeat();
    void restartTimer();
    bool establishConnection(sf::IpAddress ip,int port);
    bool isConnected();
    void setConnectionState(ConnectionState state);
    void closeConnection();
    void terminateConnection();
    sf::Packet serialize(PacketHeader header);
    void deserialize(sf::Packet &packet);
    bool sendPacket(sf::Packet packet);
    bool receivePacket(sf::Packet &packet);
    void sendAndReceivePackets();
};

#endif // NETWORK_HANDLER_HPP
