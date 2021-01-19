#pragma once
#include <vector>
#include <memory>
#include "Data/databaseobject.h"
#include "BL/AccountManager.h"
#include "Common/RequestReader.h"
#include "Common/RequestWritter.h"
#include "BL/NodesManager.h"
#include "Common/ServerResults.h"
#include "Common/ClientException.h"

//Class for user's requests treatment
class RequestHandler
{
public:
    RequestHandler(std::unique_ptr<AccountManager> & accountManager,
                   std::unique_ptr<NodesManager> & nodesManager);

    std::vector<char> handle(std::vector<char> &buffer, int socketFD);
    void destroySession(int socketFD);

private:
    //Pointer to an account manager(create, change/reset password, etc).
    std::unique_ptr<AccountManager> accountManager;
    //Pointer to a nodes manager(create, get list of nodes, etc).
    std::unique_ptr<NodesManager> nodesManager;
    //Only for test
    //std::shared_ptr<DataBaseObject> dataBase;
    //Server's bussines logic
    std::vector<char> userRegistration(std::vector<char> &buffer, int socketFD); //Method for user registration. FIRST BYTE NUMBER - 0
    std::vector<char> userAuthorization(std::vector<char> &buffer, int socketFD); //Method for user authorization. FIRST BYTE NUMBER - 1
    std::vector<char> getListOfNodes(std::vector<char> &buffer); //Method for genering Nodes' list. FIRST BYTE NUMBER - 3
    std::vector<char> createNewNode(std::vector<char> &buffer); //Method for new node's creating
};
