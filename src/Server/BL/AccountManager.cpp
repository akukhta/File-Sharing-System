#include "AccountManager.h"

AccountManager::AccountManager(std::unique_ptr<AbstractAccountRepository> & accountRepository)
    : accountRepository(std::move(accountRepository))
{
    ;
}

//Creates a new user's account
std::uint32_t AccountManager::createAccount(std::string const & email, std::string const & password, int socketFD)
{
      return accountRepository->createAccount(email, password, socketFD);
}

//Log in
std::uint32_t AccountManager::logIn(std::string const & email, std::string const & password, int socketFD)
{
      return accountRepository->logIn(email,password,socketFD);
}
