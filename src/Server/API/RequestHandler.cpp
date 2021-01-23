#include "RequestHandler.h"

RequestHandler::RequestHandler(std::unique_ptr<IAccountManager>  accountManager,
        std::unique_ptr<INodesManager>  nodesManager) : accountManager(std::move(accountManager)),
            nodesManager(std::move(nodesManager))
{ }

std::vector<char> RequestHandler::handle(std::vector<char> &buffer, int socketFD)
{
    std::vector<char> answer;
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
        break;
    case ServerOperation::CreateNewNode:
        answer = createNewNode(buffer);
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

//Method for session deleting, when client disconnects or pushes "log out" button.
void RequestHandler::destroySession(int socketFD)
{
    accountManager->closeSession(socketFD);
}
