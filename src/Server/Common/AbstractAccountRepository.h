#pragma once
#include <string>

//An interface for Account Repositories
//std::uint32_t - session token

class AbstractAccountRepository
{

public:

    virtual std::uint32_t createAccount(std::string const & email, std::string const & password, int socketFD) = 0;
    virtual std::uint32_t logIn(std::string const & email, std::string const & password, int socketFD) = 0;
    virtual void destroySession(int sockFD) = 0;
    virtual ~AbstractAccountRepository()
    {
        ;
    }

};
