#pragma once
#include <iostream>
#include <future>
#include <memory>
#include "Data/databaseobject.h"
#include "Data/EMailManager.h"
#include "Common/ClientException.h"
#include "Data/AbstractAccountRepository.h"

class AccountManager
{
public:
    AccountManager(std::unique_ptr<AbstractAccountRepository> & accountRepository);
    std::uint32_t createAccount(std::string const & email, std::string const & password, int socketFD);
    std::uint32_t logIn(std::string const & email, std::string const & password, int socketFD);
    void closeSession(int socketFD);

private:
    //Messages which send by email to client
    const std::string registrationMessage = "You have been registered in File Sharing System!", subject = "File Sharing System";
    std::unique_ptr<AbstractAccountRepository> accountRepository;

};

