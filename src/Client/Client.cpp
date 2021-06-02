#include "Client.h"
#include <QDebug>

Client::Client()
{
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
}

bool Client::connectToServer(std::string serverIP, int serverPort)
{
    serverAddress.sin_addr.s_addr = inet_addr(serverIP.c_str());
    serverAddress.sin_port = htons(serverPort);
    isConnected = (connect(socketFD, (sockaddr*) &serverAddress, sizeof(serverAddress)) == -1 ? false : true);
    return isConnected;
}

void Client::sendToServer(std::vector<char> const &buffer)
{
    size_t size = buffer.size();

    if (send(socketFD, reinterpret_cast<char*>(&size), sizeof(size_t),0) != sizeof(size_t))
    {
        throw std::runtime_error("Packet's size wasn't sended!");
    }
    if (send(socketFD, buffer.data(), buffer.size(), 0) != buffer.size())
    {
        throw std::runtime_error("Packet wasn't sended!");
    }
}

std::vector<char> Client::receiveFromServer()
{
    std::vector<char> bufferSize(sizeof(size_t));
    if (recv(socketFD, bufferSize.data(), bufferSize.size(),0) != bufferSize.size())
    {
        throw std::runtime_error("Packet's size wasn't received");
    }
    std::vector<char> buffer(*reinterpret_cast<size_t*>(bufferSize.data()));
    if (recv(socketFD, buffer.data(), buffer.size(),0) != buffer.size())
    {
        throw std::runtime_error("Packet wasn't received!");
    }

    return buffer;
}
