#pragma once
#include <iostream>
#include <thread>
#include <memory>
#include "Data/databaseobject.h"
#include "Data/EMailManager.h"
#include "Common/ClientException.h"
#include "Common/AbstractAccountRepository.h"

class AccountManager
{
public:
    AccountManager(std::unique_ptr<AbstractAccountRepository> & accountRepository);
    std::uint32_t createAccount(std::string const & email, std::string const & password, int socketFD);
    std::uint32_t logIn(std::string const & email, std::string const & password, int socketFD);
    static constexpr std::uint32_t InvalidToken = 0;
private:
    //Pointer to database object
    //std::shared_ptr<DataBaseObject> database;
    //Messages which send by email to client
    const std::string registrationMessage = "You are registered!", subject = "File sharing system";
    std::unique_ptr<AbstractAccountRepository> accountRepository;

};

