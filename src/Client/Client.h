#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <stdexcept>

class Client
{
public:
    Client();
    bool connectToServer(std::string serverIP,
                         int serverPort);
    void sendToServer(std::vector<char> const & buffer);
    std::vector<char> receiveFromServer();
private:
    int socketFD;
    sockaddr_in serverAddress;
    bool isConnected = false;

};

