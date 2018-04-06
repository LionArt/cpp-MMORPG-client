#ifndef PACKET_DATA_HPP
#define PACKET_DATA_HPP
#include <iostream>
#include <vector>

enum class PacketHeader {DISCONNECT,HEARTBEAT,HANDSHAKE,LOGIN,CHARACTER_SELECT,CONFIRM_LOGIN,GAME,PLAYER_MOVE,MESSAGE};
enum class ConnectionState {TERMINATED,DISCONNECTED,CONNECTED,HANDSHAKED,LOGGED,ERROR,CHARACTER_SELECTED,LOGIN_CONFIRMED,IN_GAME};
enum class ConnectionError {DEFAULT,DENIED,TIMEOUT,WRONG_DATA,ACCOUNT_LOGGED,CHARACTER_LOGGED};

class PacketData
{
    public:
    unsigned int activeCharacter=0;
    std::vector<std::string> names;
    std::string login="";
    std::string password="";
    uint8_t header;
    uint8_t response;
};

#endif // PACKET_DATA_HPP
