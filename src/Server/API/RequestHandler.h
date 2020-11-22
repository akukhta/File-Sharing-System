#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "../BL/AccountManager.h"
#include <vector>
#include "../Common/databaseobject.h"

//Class for user's requests treatment
class RequestHandler
{
public:
    RequestHandler();
    std::vector<char> handle(std::vector<char> buffer);
private:
    //Pointer to account manager(create, change/reset password, etc).
    AccountManager *accountManager;
    //Only for test
    DataBaseObject *dataBase;

    std::vector<char> userRegistration(std::vector<char> buffer); //Method for user registration. FIRST BYTE NUMBER - 0
};

#endif // REQUESTHANDLER_H
