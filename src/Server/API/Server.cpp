#include "Server.h"

//Inizialasing onstructor.
//POLLSIZE - maximum users' connection
Server::Server(size_t POLLSIZE)
{
    masterSocket = socket(AF_INET,SOCK_STREAM, 0);
    this->POLLSIZE = POLLSIZE;
    masterSocketAddr.sin_family = AF_INET;
    masterSocketAddr.sin_port = htons(4441);
    masterSocketAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int r = bind(masterSocket, (sockaddr*)&masterSocketAddr, sizeof(masterSocketAddr));
    pollSet = new pollfd[POLLSIZE];
    handler = new RequestHandler;
}

//Main method for start server
void Server::run()
{
    listen(masterSocket, SOMAXCONN);
    pollSet[0].fd = masterSocket;
    pollSet[0].events = POLLIN | POLLHUP;

    while(true)
    {
        updatePollSet();
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
                if (!recv(pollSet[i].fd, reinterpret_cast<char*>(&packetSize), sizeof(std::uint32_t),0))
                {
                    closeConnection(pollSet[i].fd);
                    break;
                }
                std::vector<char> buffer(packetSize);
                if (!recv(pollSet[i].fd, buffer.data(), packetSize, 0))
                {
                    closeConnection(pollSet[i].fd);
                    break;
                }
                std::vector<char> answer = handler->handle(buffer);
                size_t size = answer.size();
                if (!send(pollSet[i].fd, reinterpret_cast<char*>(&size),sizeof(size_t),0))
                {
                    closeConnection(pollSet[i].fd);
                    break;
                }
                if (!send(pollSet[i].fd, answer.data(), size,0))
                {
                    closeConnection(pollSet[i].fd);
                    break;
                }
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
        else if (pollSet[i].revents & (POLLERR|POLLHUP|POLLNVAL))
        {
            std::cout << "Client disconnected!" << std::endl;
            connectedSockets.erase(pollSet[i].fd);
            updatePollSet();
            setSize = 1 + connectedSockets.size();
        }
    }
}

void Server::closeConnection(int sockfd)
{
        shutdown(sockfd, SHUT_RDWR);
        close(sockfd);
        connectedSockets.erase(sockfd);
}
