#include "AccountsRepository.h"

AccountsRepository::AccountsRepository(std::shared_ptr<DataBaseObject> dataBase) : dataBase(dataBase)
{
    ;
}

std::uint32_t AccountsRepository::createAccount(std::string const & email,
    std::string const & password, int socketFD)
{
    if (!dataBase)
        throw std::runtime_error("Database wasn't initialized");


    if (dataBase->insertQuery("INSERT INTO Users (Email,Password) VALUES(\"" + email + "\",\"" + password + "\");"))
    {
        return logIn(email, password, socketFD);
    }
    else
        return AbstractAccountRepository::InvalidSessionToken;
}

std::uint32_t AccountsRepository::logIn(const std::string &email, const std::string &password, int socketFD)
{
    if (!dataBase)
        throw std::runtime_error("Data wasn't initialized!");
    size_t userID;

    if (dataBase->authorizationQuery(email, password, userID))
    {
        std::uint32_t sessionToken = rand() % RAND_MAX;
        dataBase->createSessionQuery(sessionToken, socketFD,userID);
        return sessionToken;
    }
    else
        return AbstractAccountRepository::InvalidSessionToken;
}

void AccountsRepository::destroySession(int sockFD)
{
        if (!dataBase)
        {
            throw std::runtime_error("Database isn't initialized!");
        }
        else
        {
            dataBase->closeSession(sockFD);
        }
}
