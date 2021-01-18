#pragma once
#include <memory>
#include "Data/databaseobject.h"

class AccountsRepository
{
public:
    AccountsRepository(std::shared_ptr<DataBaseObject> const & dataBase);
    std::uint32_t createAccount(std::string const & email, std::string const & password, int socketFD);
    std::uint32_t logIn(std::string const & email, std::string const & password, int socketFD);
    const static std::uint32_t InvalidToken = 0;
private:
    std::shared_ptr<DataBaseObject> dataBase;
};
