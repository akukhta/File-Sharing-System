#include "Server.h"

//Inizialasing onstructor.
//POLLSIZE - maximum users' connection
Server::Server(size_t POLLSIZE)
{
    this->db = new DataBaseObject;
    this->accountManager = new AccountManager(db);
    masterSocket = socket(AF_INET,SOCK_STREAM, 0);
    this->POLLSIZE = POLLSIZE;
    masterSocketAddr.sin_family = AF_INET;
    masterSocketAddr.sin_port = htons(2441);
    masterSocketAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int r = bind(masterSocket, (sockaddr*)&masterSocketAddr, sizeof(masterSocketAddr));
    pollSet = new pollfd[POLLSIZE];
}

//Main method for start server
void Server::run()
{
    listen(masterSocket, SOMAXCONN);
    pollSet[0].fd = masterSocket;
    pollSet[0].events = POLLIN;

    while(true)
    {
        poll(pollSet, setSize, -1);
        socketsPollHandler();
    }

}

//Method for poll updating. Called if we have new connection/disconnection.
void Server::updatePollSet()
{
    size_t index = 1;
    for (auto iter = connectedSockets.begin(); iter != connectedSockets.end(); iter++)
    {
        pollSet[index].fd = *iter;
        pollSet[index].events = POLLIN | POLLHUP;
        index++;
    }
}

/*Method for sockets treatment.
 * All incoming sockets' signals processing in this method
*/
void Server::socketsPollHandler()
{
    for (size_t i = 0; i < setSize; i++)
    {
        //If socket has a data to read
        if (pollSet[i].revents & POLLIN)
        {
            if (i)
            {
                //Handling users' connections
                std::uint32_t packetSize;
                recv(pollSet[i].fd, reinterpret_cast<char*>(&packetSize), sizeof(std::uint32_t),0);
                std::vector<char> buffer(packetSize);
                recv(pollSet[i].fd, buffer.data(), packetSize, 0);
                if (*reinterpret_cast<std::uint8_t*>(&buffer[0]) == 0)
                {
                    buffer.erase(buffer.begin());
                    handle(buffer);
                }
//                if (!recv(pollSet[i].fd, buffer.data(), 256,0))
//                {
//                    shutdown(pollSet[i].fd, SHUT_RDWR);
//                    close(pollSet[i].fd);
//                    connectedSockets.erase(pollSet[i].fd);
//                }
//                else
//                    std::cout << buffer.data() << std::endl;
            }
            else
            {
                //Handling master socket for new connections
                int connectedSocket = accept(masterSocket,0,0);
                connectedSockets.insert(connectedSocket);
                std::cout << "New socket connected!" << std::endl;
                updatePollSet();
                setSize = 1 + connectedSockets.size();
            }
        }

        //If socket disconnected
        if (pollSet[i].revents & (POLLERR|POLLHUP|POLLNVAL))
        {
            std::cout << "Client disconnected!" << std::endl;
            connectedSockets.erase(pollSet[i].fd);
            updatePollSet();
            setSize = 1 + connectedSockets.size();
        }
    }
}

void Server::handle(std::vector<char> &buffer)
{
    std::uint8_t *stringSize = new std::uint8_t;
    reinterpret_cast<std::uint8_t*>(buffer[0]);
    buffer.erase(buffer.begin());
    std::string email(buffer.begin(), buffer.begin() + *stringSize);
    buffer.erase(buffer.begin() + *stringSize);
    reinterpret_cast<std::uint8_t*>(buffer[0]);
    buffer.erase(buffer.begin());
    std::string password(buffer.begin(), buffer.begin() + *stringSize);
    std::cout << accountManager->createAccount(email, password) << std::endl;

}
