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
    Server(Server const &) = delete;
    void run();

private:
    size_t POLLSIZE, setSize;
    int masterSocket;
    sockaddr_in masterSocketAddr;
    pollfd *pollSet;
    std::set<int> connectedSockets;
    void updatePollSet();
    void socketsPollHandler();
    RequestHandler *handler;
    void closeConnection(int sockfd);
};

#endif // SERVER_H
