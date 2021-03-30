#pragma once
#include <vector>
#include <memory>
#include "API/IRequestHandler.h"
#include "BL/NodesManager.h"
#include "BL/AccountManager.h"
#include <BL/FilesManager.h>
#include "Common/RequestReader.h"
#include "Common/RequestWritter.h"
#include "Common/ServerResults.h"
#include "Common/ClientException.h"
#include "Common/Logger.h"


//Class for user's requests treatment
class RequestHandler : public IRequestHandler
{
public:
    RequestHandler(std::unique_ptr<IAccountManager> accountManager,
                   std::unique_ptr<INodesManager> nodesManager,
                   std::shared_ptr<IFilesManager> filesManager);

    virtual std::vector<char> handle(std::vector<char> &buffer, int socketFD) override final;
    virtual void destroySession(int socketFD) override final;

    ~RequestHandler()
    {
        Logger::log()->debugMessage("The request handler has been destroyed!");
    }

private:
    //Pointer to an account manager(create, change/reset password, etc).
    std::unique_ptr<IAccountManager> accountManager;
    //Pointer to a nodes manager(create, get list of nodes, etc).
    std::unique_ptr<INodesManager> nodesManager;
    //Pointer to a files manager. This class used for any operaions with filesystem.
    std::shared_ptr<IFilesManager> filesManager;
    //Only for test
    //std::shared_ptr<DataBaseObject> dataBase;
    //Server's bussines logic
    std::vector<char> userRegistration(std::vector<char> &buffer, int socketFD); //Method for user registration. FIRST BYTE NUMBER - 0
    std::vector<char> userAuthorization(std::vector<char> &buffer, int socketFD); //Method for user authorization. FIRST BYTE NUMBER - 1
    std::vector<char> getListOfNodes(std::vector<char> &buffer); //Method for genering Nodes' list. FIRST BYTE NUMBER - 3
    std::vector<char> createNewNode(std::vector<char> &buffer); //Method for new node's creating
    std::vector<char> startReadingFromFile(std::vector<char> &buffer);
    std::vector<char> startWrittingToFile(std::vector<char> &buffer);
    std::vector<char> readPartOfFile(std::vector<char> &buffer);
    std::vector<char> writePartOfFile(std::vector<char> &buffer);
    std::vector<char> getFilesOfNode(std::vector<char> &buffer);
    std::vector<char> deleteFile(std::vector<char> &buffer);
    //Server's operations enum class
    enum class ServerOperation : char {
        UserRegistration = 0,
        Authorization = 1,
        GetNodesList = 3,
        CreateNewNode = 4,
        StartWritting = 5,
        StartReading = 6,
        ReadPartOfFile = 7,
        WritePartOfFile = 8,
        GetFilesOfNode = 9,
        deleteFile,
    };
};
