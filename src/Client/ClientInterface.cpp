#include "ClientInterface.h"

ClientInterface::ClientInterface(std::unique_ptr<Client> client)
    : client(std::move(client))
{
    ;
}

bool ClientInterface::connectToServer(std::string serverIP, int serverPort)
{
    return client->connectToServer(serverIP, serverPort);
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

        if (Configuration::getOS() == Configuration::OS::Linux)
        {
            crypter = std::make_unique<LinuxCrypter>(email);
        }

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
    auto buffer = writer.getBuffer();
    buffer = crypter->crypt(buffer);
    client->sendToServer(buffer);
    auto answer = client->receiveFromServer();
    RequestReader reader(answer);
    std::vector<Node> nodes;

    if (reader.read<ServerResult>() == ServerResult::Failure)
    {
        return nodes;
    }

    else
    {
        answer = crypter->crypt(answer);
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

void ClientInterface::sendFile(std::string const & fileName, std::uint32_t const nodeID)
{
    startFileSending(fileName, nodeID);
    FileRepresentation file(fileName, Permissions::ReadOnly);

    while(!file.isDone)
    {
        RequestWritter writer;
        writer.write<char>(8);
        writer.write<std::uint32_t>(sessionToken);
        auto chunk = file.read();
        writer.write<std::vector<char>>(chunk);
        client->sendToServer(writer.getBuffer());
        auto answer = client->receiveFromServer();
        RequestReader reader(answer);
        if (reader.read<ServerResult>() == ServerResult::Failure)
            throw std::runtime_error(reader.read<std::string>());
    }

}

void ClientInterface::receiveFile(std::string const & fileName,
    std::string const & destFolderName, std::uint32_t const nodeID)
{
    auto fileSize = startFileReceiving(fileName, nodeID);
    FileRepresentation file (fileName, Permissions::WriteOnly, nodeID, fileSize, destFolderName);

    while (!file.isDone)
    {
        RequestWritter writer;
        writer.write<char>(7);
        writer.write<std::uint32_t>(sessionToken);
        client->sendToServer(writer.getBuffer());
        auto answer = client->receiveFromServer();

        RequestReader reader(answer);

        if (reader.read<ServerResult>() == ServerResult::Failure)
            throw std::runtime_error(reader.read<std::string>());

        auto chunk = reader.read<std::vector<char>>();
        file.write(chunk);
    }
}

void ClientInterface::startFileSending(std::string const & fileName, std::uint32_t const nodeID)
{
    std::string nameWithoutPath = fileName.substr(fileName.find_last_of(std::filesystem::path::preferred_separator) + 1);
    RequestWritter writer;
    writer.write<char>(5);
    writer.write<std::uint32_t>(sessionToken);
    writer.write<std::uint32_t>(nodeID);
    writer.write<std::string>(nameWithoutPath);
    std::uint64_t fileSize = std::filesystem::file_size(fileName);
    writer.write<std::uint64_t>(fileSize);
    client->sendToServer(writer.getBuffer());
    auto answer = client->receiveFromServer();
    RequestReader reader(answer);
    if (reader.read<ServerResult>() == ServerResult::Failure)
        throw std::runtime_error("Couldn`t send file to server!");
}

std::uint64_t ClientInterface::startFileReceiving(std::string const & fileName, std::uint32_t const nodeID)
{
    RequestWritter writer;
    writer.write<char>(6);
    writer.write<std::uint32_t>(sessionToken);
    writer.write<std::uint32_t>(nodeID);
    writer.write<std::string>(fileName);
    client->sendToServer(writer.getBuffer());
    auto answer = client->receiveFromServer();
    RequestReader reader(answer);

    if (reader.read<ServerResult>() == ServerResult::Failure)
        throw std::runtime_error("Cannot download a file!");

    std::uint64_t size = reader.read<std::uint64_t>();
    return size;
}



std::vector<std::string> ClientInterface::getFiles(std::uint32_t nodeID)
{
    RequestWritter writer;
    writer.write<char>(9);
    writer.write<std::uint32_t>(nodeID);
    client->sendToServer(writer.getBuffer());
    auto answer = client->receiveFromServer();
    RequestReader reader(answer);

    if (reader.read<ServerResult>() == ServerResult::Failure)
    {
        throw std::runtime_error("Cannot get a files list!");
    }

    std::vector<std::string> files;
    size_t filesSize = reader.read<size_t>();

    for (size_t i = 0; i < filesSize; i++)
    {
        files.push_back(reader.read<std::string>());
    }

    return files;
}

void ClientInterface::deleteFile(std::uint32_t nodeID, const std::string &fileName)
{
    RequestWritter writer;
    writer.write<char>(10);
    writer.write<std::uint32_t>(nodeID);
    writer.write<std::string>(fileName);
    client->sendToServer(writer.getBuffer());
    auto answer = client->receiveFromServer();
    RequestReader reader(answer);

    if (reader.read<ServerResult>() == ServerResult::Failure)
    {
        throw std::runtime_error(reader.read<std::string>());
    }
}
