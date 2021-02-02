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
        {
            std::string const nodeID = reader.read<std::string>();
            std::string const deletingDate = reader.read<std::string>();
            nodes.emplace_back(nodeID, deletingDate);
        }
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
    std::string const deletingDate = Configuration::getDeletingDate(lifeTimeInMins);
    writer.write<std::string>(deletingDate);
    client->sendToServer(writer.getBuffer());
    auto answer = client->receiveFromServer();
    RequestReader reader(answer);

    if (reader.read<ServerResult>() == ServerResult::Failure)
    {
        throw std::runtime_error(reader.read<std::string>());
    }

    std::uint32_t nodeID = reader.read<std::uint32_t>();
    return Node(std::to_string(nodeID), deletingDate);
}

void ClientInterface::sendFile(std::string const & fileName, size_t const nodeID)
{
    startFileSending(fileName, nodeID);
    FileRepresentation file(fileName, Permissions::ReadOnly);

    while(!file.isDone)
    {
        RequestWritter writer;
        writer.write<char>(8);
        writer.write<std::uint32_t>(sessionToken);
        auto chunk = file.read();
        writer.write<std::vector<unsigned char>>(chunk);
        client->sendToServer(writer.getBuffer());
        auto answer = client->receiveFromServer();
        RequestReader reader(answer);
        if (reader.read<ServerResult>() == ServerResult::Failure)
            throw std::runtime_error(reader.read<std::string>());
    }

}

void ClientInterface::startFileSending(std::string const & fileName, size_t const nodeID)
{
    std::string nameWithoutPath = fileName.substr(fileName.find_last_of(std::filesystem::path::preferred_separator) + 1);
    RequestWritter writer;
    writer.write<char>(5);
    writer.write<std::uint32_t>(sessionToken);
    writer.write<size_t>(nodeID);
    writer.write<std::string>(nameWithoutPath);
    std::uint64_t fileSize = std::filesystem::file_size(fileName);
    writer.write<std::uint64_t>(fileSize);
    client->sendToServer(writer.getBuffer());
    auto answer = client->receiveFromServer();
    RequestReader reader(answer);
    if (reader.read<ServerResult>() == ServerResult::Failure)
        throw std::runtime_error("Couldn`t send file to server!");
}
