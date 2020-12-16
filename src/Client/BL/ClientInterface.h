#pragma once
#include <memory>
#include "BL/Client.h"
#include "Common/Configuration.h"
#include "Common/RequestReader.h"
#include "Common/RequestWritter.h"

class ClientInterface
{
public:
    ClientInterface(std::unique_ptr<Client> client);
    bool connectToServer(std::string serverIP = Configuration::getServerIP(),
                         int serverPort = Configuration::getServerPort());
    bool authorize(std::string email, std::string password, bool isRegister = true);
private:
    std::unique_ptr<Client> client;
    std::uint32_t sessionToken;
    bool isAuthorized = false;
};

