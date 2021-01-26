#pragma once
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <poll.h>
#include <set>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <memory>
#include "Common/Configuration.h"
#include "Common/Logger.h"
#include "BL/AccountManager.h"
#include "API/RequestHandler.h"

class Server
{
public:
    explicit Server(std::unique_ptr<IRequestHandler> handler, std::string IP = Configuration::getDefaultIP(),
                    int port = Configuration::getDafultPort(),size_t POLLSIZE = 32);
    /*
     * Because we don't need copy of this server.
     * If we can have copy we get some problems with server's port.
     * TODO: Maybe need to make this class as singleton
    */
    //Server(Server const &) = delete;
    void run();

    ~Server()
    {
        Logger::log()->debugMessage("Server has been deleted!");
    }

private:
    /*
     * POLSIZE - maximum number of connections;
     * setSize - current count of connected sockets and master socket.
    */
    size_t POLLSIZE, setSize;
    //Main server's socket.
    int masterSocket;
    //Server's address.
    sockaddr_in masterSocketAddr;
    //Pollset structure. Use for poll.
    std::vector<pollfd> pollSet;
    //Set of connected sockets.
    std::set<int> connectedSockets;
    void updatePollSet();
    void socketsPollHandler();
    //Pointer to server request handler
    std::unique_ptr<IRequestHandler> handler;
    void closeConnection(int sockfd);
    std::vector<char> reciveFromClient(int sockfd, size_t size);
    void sendToClient(int sockfd, char* const buffer, size_t bufferSize);
};

