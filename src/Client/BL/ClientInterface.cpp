#include "ClientInterface.h"

ClientInterface::ClientInterface(std::unique_ptr<Client> client) : client(std::move(client))
{
    ;
}

bool ClientInterface::connectToServer(std::string serverIP, int serverPort)
{
    client->connectToServer(serverIP, serverPort);
}

bool ClientInterface::authorize(std::string email, std::string password, bool isRegister)
{
    RequestWritter writer;
    writer.write<char>(isRegister ? 0 : 1);
    writer.write<std::string>(email);
    writer.write<std::string>(password);
    client->sendToServer(writer.getBuffer());
    auto answer = client->receiveFromServer();
    RequestReader reader(std::make_shared<std::vector<char>>(answer));
    if (reader.read<char>())
    {
        sessionToken = reader.read<std::uint32_t>();
        return true;
    }
    else
    {
        return false;
    }
}
