#include "AccountManager.h"

AccountManager::AccountManager(DataBaseObject *db) : database(db)
{
    //srand(time(NULL));
    //rand();
}

std::uint32_t AccountManager::createAccount(std::string email, std::string password)
{
    if (database == nullptr)
        throw std::runtime_error("Database didn't initialized");
    if (!database->query("INSERT INTO User(email,password) VALUES(\"" + email + "\",\"" + password + "\");"))
    {
        //std::thread(EMailManager::Send, email,subject, registrationMessage).detach();
        EMailManager::Send(email, subject, registrationMessage);
        return rand() % RAND_MAX;
    }
    else
        return 0x0000000000;
}
