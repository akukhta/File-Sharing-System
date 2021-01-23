#pragma once
#include <string>

class IAccountManager
{
public:
    virtual ~IAccountManager() = default;
    virtual std::uint32_t createAccount(std::string const & email, std::string const & password, int socketFD) = 0;
    virtual std::uint32_t logIn(std::string const & email, std::string const & password, int socketFD) = 0;
    virtual void closeSession(int socketFD) = 0;
};
