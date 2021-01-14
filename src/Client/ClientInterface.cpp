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
    RequestReader reader(answer);
    if (reader.read<ServerResult>() == ServerResult::Success)
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
    RequestReader reader(answer);
    std::vector<Node> nodes;

    if (reader.read<ServerResult>() == ServerResult::Failure)
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

Node ClientInterface::createNode(long long lifeTimeInMins)
{
    RequestWritter writer;
    writer.write<char>(4);
    writer.write<std::uint32_t>(sessionToken);
    writer.write<long long>(lifeTimeInMins);
    client->sendToServer(writer.getBuffer());
    auto answer = client->receiveFromServer();
    RequestReader reader(answer);

    if (reader.read<ServerResult>() == ServerResult::Failure)
    {
        throw std::runtime_error(reader.read<std::string>());
    }

    std::uint32_t nodeID = reader.read<std::uint32_t>();
    return Node(std::to_string(nodeID));
}
