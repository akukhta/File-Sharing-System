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
    std::vector<char> handle(std::vector<char> buffer);
private:
    //Pointer to account manager(create, change/reset password, etc).
    std::unique_ptr<AccountManager> accountManager;
    //Only for test
    std::unique_ptr<DataBaseObject> dataBase;
    std::vector<char> userRegistration(std::vector<char> buffer); //Method for user registration. FIRST BYTE NUMBER - 0
};
