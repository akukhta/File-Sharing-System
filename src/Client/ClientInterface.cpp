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
        isAuthorized = true;
        return true;
    }
    else
    {
        isAuthorized = false;
        return false;
    }
}

std::vector<Node> ClientInterface::getNodes()
{
    RequestWritter writer;
    writer.write<char>(3);
    writer.write<std::uint32_t>(sessionToken);
    client->sendToServer(writer.getBuffer());
    auto answer = client->receiveFromServer();
    RequestReader reader(std::make_shared<std::vector<char>>(answer));
    std::vector<Node> nodes;

    if (!reader.read<char>())
    {
        return nodes;
    }

    else
    {
        size_t nodesCount = reader.read<size_t>();
        for (size_t i = 0; i < nodesCount; i++)
            nodes.emplace_back(reader.read<std::string>());
    }

    return nodes;
}

bool ClientInterface::authorized()
{
    return isAuthorized;
}
