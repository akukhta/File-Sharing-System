#include "AccountManager.h"

AccountManager::AccountManager(std::unique_ptr<AbstractAccountRepository> accountRepository)
    : accountRepository(std::move(accountRepository))
{
     Logger::log()->debugMessage("The account manager has been created!");
}

//Creates a new user's account
std::uint32_t AccountManager::createAccount(std::string const & email, std::string const & password, int socketFD)
{
      Logger::log()->infoMessage("Account manager: a new account creating!");
      auto sessionToken = accountRepository->createAccount(email, password, socketFD);

      if (sessionToken != AbstractAccountRepository::InvalidSessionToken)
      {
          //Seding a message as an async task
          auto asyncTask = std::async(std::launch::async, [](auto const & email, auto const & subject, auto const & message){
              EMailManager::Send(email, subject, message);
          }, email, subject, registrationMessage);
      }

      return sessionToken;
}


//Log in
std::uint32_t AccountManager::logIn(std::string const & email, std::string const & password, int socketFD)
{
      Logger::log()->infoMessage("Account manager: user authorization!");
      return accountRepository->logIn(email,password,socketFD);
}

void AccountManager::closeSession(int socketFD)
{
    accountRepository->destroySession(socketFD);
}
