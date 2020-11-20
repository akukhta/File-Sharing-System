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
#include "databaseobject.h"
#include "AccountManager.h"

class Server
{
public:
    Server(size_t POLLSIZE = 32);
    void run();

private:
    size_t POLLSIZE, setSize;
    int masterSocket;
    sockaddr_in masterSocketAddr;
    pollfd *pollSet;
    std::set<int> connectedSockets;
    void updatePollSet();
    void socketsPollHandler();
    void handle(std::vector<char> &buffer);
    DataBaseObject *db;
    AccountManager *accountManager;
};

#endif // SERVER_H
