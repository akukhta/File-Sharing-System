#pragma once
#include <memory>
#include "Data/AbstractAccountRepository.h"
#include "Data/databaseobject.h"

class AccountsRepository : public AbstractAccountRepository
{
public:

    AccountsRepository(std::shared_ptr<DataBaseObject> dataBase);

    virtual std::uint32_t createAccount(std::string const & email,
        std::string const & password, int socketFD) override final;

    virtual std::uint32_t logIn(std::string const & email,
        std::string const & password, int socketFD) override final;

    virtual void destroySession(int sockFD) override;

    ~AccountsRepository()
    {
        std::cout << "Accounts repository has been deleted!" << std::endl;
    }

private:
    std::shared_ptr<DataBaseObject> dataBase;
};
