#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <poll.h>
#include <set>
#include <vector>
#include <unistd.h>
#include <iostream>
#include "../Common/databaseobject.h"
#include "../BL/AccountManager.h"
#include "RequestHandler.h"

class Server
{
public:
    explicit Server(size_t POLLSIZE = 32);
    /*
     * Because we don't need copy of this server.
     * If we can have copy we get some problems with server's port.
     * TODO: Maybe need to make this class as singleton
    */
    Server(Server const &) = delete;
    void run();

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
    pollfd *pollSet;
    //Set of connected sockets.
    std::set<int> connectedSockets;
    void updatePollSet();
    void socketsPollHandler();
    //Pointer to server request handler
    RequestHandler *handler;
    void closeConnection(int sockfd);
    std::vector<char> reciveFromClient(int sockfd, size_t size);
    void sendToClient(int sockfd, char* const buffer, size_t bufferSize);
};

#endif // SERVER_H
