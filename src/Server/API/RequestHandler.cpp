#include "RequestHandler.h"

RequestHandler::RequestHandler(std::unique_ptr<IAccountManager>  accountManager,
        std::unique_ptr<INodesManager>  nodesManager, std::shared_ptr<IFilesManager>  filesManager,  std::unique_ptr<Crypter> cryptographyHandler) : accountManager(std::move(accountManager)),
            nodesManager(std::move(nodesManager)), filesManager(std::move(filesManager)), cryptographyHandler(std::move(cryptographyHandler))
{ }

std::vector<char> RequestHandler::handle(std::vector<char> &buffer, int socketFD)
{
    std::vector<char> answer;

    //Decrypting of buffer
    try {
        buffer = cryptographyHandler->cryptBuffer(socketFD, buffer);
    }  catch (std::runtime_error const & err) {
        Logger::log()->errorMessage(err.what());
    }

    ServerOperation action = static_cast<ServerOperation>(buffer[0]);
    buffer.erase(buffer.begin());

    switch (action) {
    case ServerOperation::UserRegistration:
        answer = userRegistration(buffer, socketFD);
        break;
    case ServerOperation::Authorization:
        answer = userAuthorization(buffer, socketFD);
        break;
    case ServerOperation::GetNodesList:
        answer = getListOfNodes(buffer);
        answer = cryptographyHandler->cryptBuffer(socketFD, answer);
        break;
    case ServerOperation::CreateNewNode:
        answer = createNewNode(buffer);
        answer = cryptographyHandler->cryptBuffer(socketFD, answer);
        break;
    case ServerOperation::StartReading:
        answer = startReadingFromFile(buffer);
        answer = cryptographyHandler->cryptBuffer(socketFD, answer);
        break;
    case ServerOperation::StartWritting:
        answer = startWrittingToFile(buffer);
        answer = cryptographyHandler->cryptBuffer(socketFD, answer);
        break;
    case ServerOperation::ReadPartOfFile:
        answer = readPartOfFile(buffer);
        answer = cryptographyHandler->cryptBuffer(socketFD, answer);
        break;
    case ServerOperation::WritePartOfFile:
        answer = writePartOfFile(buffer);
        answer = cryptographyHandler->cryptBuffer(socketFD, answer);
        break;
    case ServerOperation::GetFilesOfNode:
        answer = getFilesOfNode(buffer);
        answer = cryptographyHandler->cryptBuffer(socketFD, answer);
        break;
    case ServerOperation::deleteFile:
        answer = deleteFile(buffer);
        answer = cryptographyHandler->cryptBuffer(socketFD, answer);
        break;
    default:
        break;
    }

    return answer;
}

//Only for test. In future it will be rewritted.
std::vector<char> RequestHandler::userRegistration(std::vector<char> &buffer, int socketFD)
{
    Logger::log()->infoMessage("An user registration handling");
    RequestReader reader(buffer);
    RequestWritter writer;
    try{
            const std::string email = reader.read<std::string>();
            const std::string password = reader.read<std::string>();
            std::uint32_t sessionToken = accountManager->createAccount(email, password, socketFD);
            writer.write<ServerResult>(ServerResult::Success);
            writer.write<std::uint32_t>(sessionToken);
        }
        catch (std::runtime_error const & err)
        {
            std::string errorMessage(err.what());
            writer.write<ServerResult>(ServerResult::Failure);
            writer.write<std::string>(errorMessage);
        }

    auto responce = writer.getBuffer();
    return responce;
}


//Method for user authorizating. Returns sessiong token.
std::vector<char> RequestHandler::userAuthorization(std::vector<char> &buffer, int socketFD)
{
    Logger::log()->infoMessage("An authorization handling");
    RequestReader reader(buffer);
    RequestWritter writer;
    try
    {
        std::string const email = reader.read<std::string>();
        std::string const password = reader.read<std::string>();
        std::uint32_t sessionToken = accountManager->logIn(email, password, socketFD);

        if (sessionToken != AbstractAccountRepository::InvalidSessionToken)
        {
            writer.write<ServerResult>(ServerResult::Success);
            writer.write<std::uint32_t>(sessionToken);
            cryptographyHandler->registerUserToCrypter(socketFD, email);
        }
        else
        {
            Logger::log()->errorMessage("Authorization has been failed");
            writer.write<ServerResult>(ServerResult::Failure);
        }
    } catch (std::runtime_error const & err)
    {
        writer.write<ServerResult>(ServerResult::Failure);
        writer.write<std::string>(Configuration::getServerErrorMessage());
    }

    return writer.getBuffer();
}

std::vector<char> RequestHandler::getListOfNodes(std::vector<char> &buffer)
{
    Logger::log()->infoMessage("Get nodes request handling");
    RequestReader reader(buffer);
    const std::uint32_t sessionToken = reader.read<std::uint32_t>();
    RequestWritter writer;

    try
    {
        auto nodesList = nodesManager->getNodesList(sessionToken);
        writer.write<ServerResult>(ServerResult::Success);
        writer.write<size_t>(nodesList.size());

        for (auto const & node : nodesList)
        {
            writer.write<std::string>(node.first); //First - A Node's ID
            writer.write<std::string>(node.second); // Second - A Node's deleting's time
        }

    }

    catch (std::runtime_error const & err)
    {
        Logger::log()->errorMessage("Cannot get a nodes` list!");
        writer.write<ServerResult>(ServerResult::Failure);
        writer.write<std::string>("Cannot get a nodes' list!");
        return writer.getBuffer();
    }

    return writer.getBuffer();
}

std::vector<char> RequestHandler::createNewNode(std::vector<char> &buffer)
{
    Logger::log()->infoMessage("New nodes creating handling");
    RequestReader reader(buffer);
    RequestWritter writer;
    const std::uint32_t sessionToken = reader.read<std::uint32_t>();
    const std::string deletingDate = reader.read<std::string>();
    std::uint32_t nodeID;

    try{
        nodeID = nodesManager->createNode(sessionToken, deletingDate);
        if (nodeID)
        {
            writer.write<ServerResult>(ServerResult::Success);
            writer.write<std::uint32_t>(nodeID);
        }
        else
        {
            Logger::log()->errorMessage("Cannot create a new node!");
            writer.write<ServerResult>(ServerResult::Failure);
            writer.write<std::string>("Couldn`t create a new node!");
        }
    } catch (std::runtime_error const & err)
    {
        writer.write<ServerResult>(ServerResult::Failure);
        writer.write<std::string>(Configuration::getServerErrorMessage());
    }

    return writer.getBuffer();
}

std::vector<char> RequestHandler::startReadingFromFile(std::vector<char> &buffer)
{
    RequestReader reader(buffer);
    RequestWritter writer;
    const std::uint32_t sessionToken = reader.read<std::uint32_t>();
    const std::uint32_t nodeID = reader.read<std::uint32_t>();
    const std::string fileName = reader.read<std::string>();

    try{

        std::uint64_t size = filesManager->startReading(nodeID, sessionToken, fileName);
        writer.write<ServerResult>(ServerResult::Success);
        writer.write<std::uint64_t>(size);

    } catch (std::runtime_error const & err)
    {
        writer.write<ServerResult>(ServerResult::Failure);
        writer.write<std::string>(Configuration::getServerErrorMessage());
    }

    return writer.getBuffer();
}

std::vector<char> RequestHandler::startWrittingToFile(std::vector<char> &buffer)
{
    RequestReader reader(buffer);
    RequestWritter writer;
    const std::uint32_t sessionToken = reader.read<std::uint32_t>();
    const std::uint32_t nodeID = reader.read<std::uint32_t>();
    const std::string fileName = reader.read<std::string>();
    const std::uint64_t fileSize = reader.read<std::uint64_t>();

    try{

        filesManager->startWritting(nodeID, sessionToken, fileName, fileSize);
        writer.write<ServerResult>(ServerResult::Success);

    } catch (std::runtime_error const &)
    {
        writer.write<ServerResult>(ServerResult::Failure);
    }

    return writer.getBuffer();
}


std::vector<char> RequestHandler::readPartOfFile(std::vector<char> & buffer)
{
    RequestReader reader(buffer);
    RequestWritter writer;
    const std::uint32_t sessionToken = reader.read<std::uint32_t>();

    try{

        auto partOfFile = filesManager->readPartOfFile(sessionToken);
        writer.write<ServerResult>(ServerResult::Success);
        writer.write<std::vector<char>>(partOfFile);

    } catch (std::runtime_error const &)
    {
        writer.write<ServerResult>(ServerResult::Failure);
        writer.write<std::string>(Configuration::getServerErrorMessage());
    }

    return writer.getBuffer();
}

std::vector<char> RequestHandler::writePartOfFile(std::vector<char> & buffer)
{
    RequestReader reader(buffer);
    RequestWritter writer;
    const std::uint32_t sessionToken = reader.read<std::uint32_t>();
    const std::vector<char> chunk = reader.read<std::vector<char>>();

    try
    {

        filesManager->writePartOfFile(chunk, sessionToken);
        writer.write<ServerResult>(ServerResult::Success);

    } catch (std::runtime_error const &)
    {
        writer.write<ServerResult>(ServerResult::Failure);
        writer.write<std::string>(Configuration::getServerErrorMessage());
    }

    return writer.getBuffer();
}

std::vector<char> RequestHandler::getFilesOfNode(std::vector<char> &buffer)
{
    RequestReader reader(buffer);
    RequestWritter writer;
    const std::uint32_t nodeID = reader.read<std::uint32_t>();

    try
    {
        auto files = filesManager->getFilesList(nodeID);
        writer.write<ServerResult>(ServerResult::Success);
        writer.write<size_t>(files.size());

        for (auto const & file : files)
        {
            writer.write<std::string>(file);
        }

    } catch (std::runtime_error const &)
    {
        writer.write<ServerResult>(ServerResult::Failure);
        writer.write<std::string>(Configuration::getServerErrorMessage());
    }

    return writer.getBuffer();
}

std::vector<char> RequestHandler::deleteFile(std::vector<char> &buffer)
{
    RequestReader reader(buffer);
    RequestWritter writer;
    const std::uint32_t nodeID = reader.read<std::uint32_t>();
    const std::string fileName = reader.read<std::string>();

    try{
        filesManager->deleteFile(nodeID, fileName);
        writer.write<ServerResult>(ServerResult::Success);
    }
    catch (std::runtime_error const & err)
    {
        writer.write<ServerResult>(ServerResult::Failure);
        writer.write<std::string>(err.what());
    }

    return writer.getBuffer();
}

//Method for session deleting, when client disconnects or pushes "log out" button.
void RequestHandler::destroySession(int socketFD)
{
    accountManager->closeSession(socketFD);
    cryptographyHandler->deleteCrypter(socketFD);
}
