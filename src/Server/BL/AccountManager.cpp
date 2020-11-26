#include "AccountManager.h"


AccountManager::AccountManager(std::shared_ptr<DataBaseObject> db) : database(db)
{
    srand(time(NULL));
    rand();
}

//Creates a new user's account
std::uint32_t AccountManager::createAccount(std::string email, std::string password)
{
    if (!database)
        throw std::runtime_error("Database didn't initialized");
    if (!database->query("INSERT INTO User(email,password) VALUES(\"" + email + "\",\"" + password + "\");"))
    {
        //std::thread(EMailManager::Send, email,subject, registrationMessage).detach();
        EMailManager::Send(email, subject, registrationMessage);
        //It's testing return value.
        return rand() % RAND_MAX;
    }
    else
        //If have some problems with registration, send 0 as session token.
        //0 - incorrect session token
        return 0x0000000000;
}
