#include "Server.h"

//Inizialasing onstructor.
//POLLSIZE - maximum users' connection
Server::Server(std::unique_ptr<IRequestHandler> handler, std::string IP, int port,size_t POLLSIZE)
    : handler(std::move(handler))
{
    masterSocket = socket(AF_INET,SOCK_STREAM, 0);
    this->POLLSIZE = POLLSIZE;
    masterSocketAddr.sin_family = AF_INET;
    masterSocketAddr.sin_port = port;
    masterSocketAddr.sin_addr.s_addr = inet_addr(IP.c_str());

    if (bind(masterSocket, (sockaddr*)&masterSocketAddr, sizeof(masterSocketAddr)) == -1)
    {
        throw std::runtime_error("The Server hasn`t been binded!");
    }

    pollSet = std::vector<pollfd>(POLLSIZE);

    //handler = std::make_unique<RequestHandler>();

    setSize = 1;

    Logger::log()->debugMessage("Server has been created!");
}

//Main method for start server
void Server::run()
{
    listen(masterSocket, SOMAXCONN);
    pollSet[0].fd = masterSocket;
    pollSet[0].events = POLLIN;

    while(true)
    {
        poll(pollSet.data(), setSize, -1);
        socketsPollHandler();
    }

}

//Method for poll updating. Called if we have new connection/disconnection.
//This method put sockets in poll set for future communication
void Server::updatePollSet()
{
    setSize = 1 + connectedSockets.size();
    size_t index = 1;
    for (auto iter : connectedSockets)
    {
        pollSet[index].fd = iter;
        pollSet[index].events = POLLIN;
        index++;
    }
}

/*Method for sockets treatment.
 * All incoming sockets' signals processing in this method
*/
void Server::socketsPollHandler()
{
    for (auto sock : pollSet)
    {
        //If socket has a data to read
        if (sock.revents & POLLIN)
        {
            if (sock.fd != pollSet[0].fd)
            {
                //Handling users' connections
                //Sockets with descriptors greater than zero - clients' sockets
                try {
                   std::size_t packetSize; //Size of packet
                   std::vector<char> buf; //Buffer for receiving
                   buf = reciveFromClient(sock.fd, sizeof(size_t)); //Receiving size
                   packetSize = *reinterpret_cast<size_t*>(buf.data()); //Cast from char to size_t
                   buf = reciveFromClient(sock.fd, packetSize); //Receiving "packetSize" bytes of data
                   std::vector<char> answer = handler->handle(buf, sock.fd); //Run needed function
                   size_t size = answer.size(); // Size of answer to client
                   sendToClient(sock.fd, reinterpret_cast<char*>(&size), sizeof(size_t)); //Send size to client
                   sendToClient(sock.fd, answer.data(), size); //Send answer to client
                }  catch (std::runtime_error const &err) {
                    //Close connection if we have problems
                    std::cout << err.what() << std::endl;
                    closeConnection(sock.fd); //Close connection, if socket is unaviable
                    updatePollSet(); //Update pollset
                    break;
                }
            }
            else
            {
                //Handling master socket for new connections.
                //Master socket has null index in pollSet
                int connectedSocket = accept(masterSocket,0,0);
                connectedSockets.insert(connectedSocket);
                Logger::log()->debugMessage("New client has been connected!");
                updatePollSet();
            }
        }

        //If have errors with socket
        else if (sock.revents & (POLLERR|POLLHUP|POLLNVAL))
        {
            Logger::log()->errorMessage("Socket`s error!");
            connectedSockets.erase(sock.fd);
            updatePollSet();
        }
    }
}

//Closes client's connection
void Server::closeConnection(int sockfd)
{
        Logger::log()->debugMessage("A client has been disconnected!");
        handler->destroySession(sockfd);
        shutdown(sockfd, SHUT_RDWR);
        close(sockfd);
        connectedSockets.erase(sockfd);
        updatePollSet();
}

//Receive data from client
std::vector<char> Server::reciveFromClient(int sockfd, size_t size)
{
    std::vector<char> buffer(size);
    if (recv(sockfd, buffer.data(),size,MSG_NOSIGNAL) != static_cast<ssize_t>(size))
        throw std::runtime_error("Receiving error");
    else
        return buffer;
}

//Send data to client
void Server::sendToClient(int sockfd, char* const buffer, size_t bufferSize)
{
    if (send(sockfd, buffer,bufferSize,0) != static_cast<ssize_t>(bufferSize))
        throw std::runtime_error("Sending error");
    else
        return;
}
