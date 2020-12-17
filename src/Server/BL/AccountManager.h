#pragma once
#include <iostream>
#include <thread>
#include <memory>
#include "Data/databaseobject.h"
#include "Data/EMailManager.h"

class AccountManager
{
public:
    AccountManager(std::shared_ptr<DataBaseObject> db);
    std::uint32_t createAccount(std::string email, std::string password, int socketFD);
    std::uint32_t logIn(std::string email, std::string password, int socketFD);
private:
    //Pointer to database object
    std::shared_ptr<DataBaseObject> database;
    //Messages which send by email to client
    const std::string registrationMessage = "You are registered!", subject = "File sharing system";
};

