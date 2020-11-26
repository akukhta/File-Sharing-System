#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H
#include <iostream>
#include <sqlite3.h>
#include "../Common/databaseobject.h"
#include <thread>
#include "../Common/EMailManager.h"
#include <memory>

class AccountManager
{
public:
    AccountManager(std::shared_ptr<DataBaseObject> db);
    std::uint32_t createAccount(std::string email, std::string password);
private:
    //Pointer to database object
    std::shared_ptr<DataBaseObject> database;
    //Messages which send by email to client
    const std::string registrationMessage = "You are registered!", subject = "File sharing system";
};

#endif // ACCOUNTMANAGER_H
