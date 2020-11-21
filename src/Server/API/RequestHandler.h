#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "../BL/AccountManager.h"
#include <vector>
#include "../Common/databaseobject.h"

class RequestHandler
{
public:
    RequestHandler();
    std::vector<char> handle(std::vector<char> buffer);
private:
    AccountManager *accountManager;
    DataBaseObject *dataBase;
};

#endif // REQUESTHANDLER_H
