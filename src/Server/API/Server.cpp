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

                try {
                   std::vector<char> buf;
                   buf = reciveFromClient(pollSet[i].fd, sizeof(std::uint32_t));
                   packetSize = *reinterpret_cast<std::uint32_t*>(buf.data());
                   buf = reciveFromClient(pollSet[i].fd, packetSize);
                   std::vector<char> answer = handler->handle(buf);
                   size_t size = answer.size();
                   sendToClient(pollSet[i].fd, reinterpret_cast<char*>(&size), sizeof(size_t));
                   sendToClient(pollSet[i].fd, answer.data(), size);
                }  catch (std::runtime_error err) {
                    closeConnection(pollSet[i].fd);
                    continue;
                }
//                if (!recv(pollSet[i].fd, reinterpret_cast<char*>(&packetSize), sizeof(std::uint32_t),0))
//                {
//                    closeConnection(pollSet[i].fd);
//                    break;
//                }
//                std::vector<char> buffer(packetSize);
//                if (!recv(pollSet[i].fd, buffer.data(), packetSize, 0))
//                {
//                    closeConnection(pollSet[i].fd);
//                    break;
//                }
//                std::vector<char> answer = handler->handle(buffer);
//                size_t size = answer.size();
//                if (!send(pollSet[i].fd, reinterpret_cast<char*>(&size),sizeof(size_t),0))
//                {
//                    closeConnection(pollSet[i].fd);
//                    break;
//                }
//                if (!send(pollSet[i].fd, answer.data(), size,0))
//                {
//                    closeConnection(pollSet[i].fd);
//                    break;
//                }
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
        close(sockfd);
        connectedSockets.erase(sockfd);
}

std::vector<char> Server::reciveFromClient(int sockfd, size_t size)
{
    std::vector<char> buffer(size);
    if (recv(sockfd, buffer.data(),size,MSG_NOSIGNAL) != size)
        throw std::runtime_error("Receiving error");
    else
        return buffer;
}

void Server::sendToClient(int sockfd, char* const buffer, size_t bufferSize)
{
    if (send(sockfd, buffer,bufferSize,0) != bufferSize)
        throw std::runtime_error("Sending error");
    else
        return;
}
