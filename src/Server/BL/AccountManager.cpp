#include "AccountManager.h"

AccountManager::AccountManager(DataBaseObject *db) : database(db)
{
    srand(time(NULL));
    rand();
}

std::uint32_t AccountManager::createAccount(std::string email, std::string password)
{
    if (database == nullptr)
        throw std::runtime_error("Database didn't initialized");

    if (database->query("INSERT INTO user VALUES(" + email + "," + password + ")"))
        return rand() % RAND_MAX;
    else
        return 0x0000000000;
}
