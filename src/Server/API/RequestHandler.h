#pragma once
#include <vector>
#include <memory>
#include "Data/databaseobject.h"
#include "BL/AccountManager.h"
#include "Common/RequestReader.h"
#include "Common/RequestWritter.h"

//Class for user's requests treatment
class RequestHandler
{
public:
    RequestHandler();
    std::vector<char> handle(std::vector<char> buffer, int socketFD);
    void destroySession(int socketFD);
private:
    //Pointer to account manager(create, change/reset password, etc).
    std::unique_ptr<AccountManager> accountManager;
    //Only for test
    std::shared_ptr<DataBaseObject> dataBase;
    std::vector<char> userRegistration(std::vector<char> buffer, int socketFD); //Method for user registration. FIRST BYTE NUMBER - 0
    std::vector<char> userAuthorization(std::vector<char> buffer, int socketFD); //Method for user authorization. FIRT BYTE NUMBER - 1
};
