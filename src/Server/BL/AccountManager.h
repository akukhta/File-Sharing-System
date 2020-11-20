#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H
#include <iostream>
#include <sqlite3.h>
#include "databaseobject.h"

class AccountManager
{
public:
    AccountManager(DataBaseObject *db = nullptr);
    std::uint32_t createAccount(std::string email, std::string password);
private:
    sqlite3 *db;
    DataBaseObject *database;
};

#endif // ACCOUNTMANAGER_H
