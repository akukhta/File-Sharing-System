#include "AccountManager.h"


AccountManager::AccountManager(std::shared_ptr<DataBaseObject> const & db) : database(db)
{
    srand(time(NULL));
    rand();
}

//Creates a new user's account
std::uint32_t AccountManager::createAccount(std::string const & email, std::string const & password, int socketFD)
{

    if (!database)
        throw std::runtime_error("Database wasn't initialized");
    if (database->insertQuery("INSERT INTO Users (Email,Password) VALUES(\"" + email + "\",\"" + password + "\");"))
    {
        //std::thread(EMailManager::Send, email,subject, registrationMessage).detach();
        EMailManager::Send(email, subject, registrationMessage);
        //It's testing return value.
        return logIn(email, password, socketFD);
    }
    else
        //If have some problems with registration, send 0 as session token.
        //0 - incorrect session token
        return 0x0000000000;
}

//Log in
std::uint32_t AccountManager::logIn(std::string const & email, std::string const & password, int socketFD)
{
    if (!database)
        throw std::runtime_error("Data wasn't initialized!");
    size_t userID;

    if (database->authorizationQuery(email, password, userID))
    {
        std::uint32_t sessionToken = rand() % RAND_MAX;
        database->createSessionQuery(sessionToken, socketFD,userID);
        return sessionToken;
    }
    else
        return 0x00000000;
}
