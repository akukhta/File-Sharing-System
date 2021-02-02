#pragma once
#include <memory>
#include <vector>
#include <string>
#include <chrono>
#include "Client.h"
#include "Common/Configuration.h"
#include "Common/RequestReader.h"
#include "Common/RequestWritter.h"
#include "Common/Node.h"
#include "Common/FileRepresentation.h"

class ClientInterface
{
public:
    ClientInterface(std::unique_ptr<Client> client);
    bool connectToServer(std::string serverIP = Configuration::getServerIP(),
                         int serverPort = Configuration::getServerPort());
    bool authorize(std::string email, std::string password, bool isRegister = true);
    bool authorized();
    std::vector<Node> getNodes();
    void sendFile(std::string const & fileName, size_t const nodeID);
    Node createNode(long long lifeTimeInMins);

private:
    std::unique_ptr<Client> client;
    std::uint32_t sessionToken;
    void startFileSending(std::string const & fileName, size_t const nodeID);
    bool isAuthorized = false;
};

