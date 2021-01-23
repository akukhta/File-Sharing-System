#pragma once
#include <iostream>
#include <future>
#include <memory>
#include "BL/IAccountManager.h"
#include "Data/EMailManager.h"
#include "Data/AbstractAccountRepository.h"
#include "Common/ClientException.h"
#include "Common/Logger.h"

class AccountManager : public IAccountManager
{
public:
    AccountManager(std::unique_ptr<AbstractAccountRepository> accountRepository);
    std::uint32_t createAccount(std::string const & email, std::string const & password, int socketFD) override;
    std::uint32_t logIn(std::string const & email, std::string const & password, int socketFD) override;
    void closeSession(int socketFD) override;

    ~AccountManager()
    {
        Logger::log()->debugMessage("The account manager has been deleted!");
    }

private:
    //Messages which send by email to client
    const std::string registrationMessage = "You have been registered in File Sharing System!", subject = "File Sharing System";
    std::unique_ptr<AbstractAccountRepository> accountRepository;

};

