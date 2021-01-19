#pragma once
#include <memory>
#include "Common/AbstractAccountRepository.h"
#include "Data/databaseobject.h"

class AccountsRepository : public AbstractAccountRepository
{
public:

    AccountsRepository(std::shared_ptr<DataBaseObject> const & dataBase);

    virtual std::uint32_t createAccount(std::string const & email,
        std::string const & password, int socketFD) override final;

    virtual std::uint32_t logIn(std::string const & email,
        std::string const & password, int socketFD) override final;

    const static std::uint32_t InvalidToken = 0;

private:
    std::shared_ptr<DataBaseObject> dataBase;
};
