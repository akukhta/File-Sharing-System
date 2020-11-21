#include "RequestHandler.h"

RequestHandler::RequestHandler()
{
    try
    {
    this->dataBase = new DataBaseObject;
    this->accountManager = new AccountManager(dataBase);
    } catch (std::runtime_error const &err)
    {
        throw;
    }
}

std::vector<char> RequestHandler::handle(std::vector<char> buffer)
{
    switch (buffer[0]) {
    case 0:
    {
        std::vector<char> answer;
        int size = buffer[1];
        std::string email(buffer.begin() + 2, buffer.begin() + 2 + size);
        size = buffer[2 + size];
        std::string password(buffer.begin() + 3 + email.length(), buffer.begin() + 3 + email.length() + size);
        try{
            std::uint32_t sessionToken = accountManager->createAccount(email, password);
            answer = std::vector<char>(5);
            answer[0] = 1;
            char *sessionnPtr = reinterpret_cast<char*>(&sessionToken);
            for (int i = 0; i < 4; i++)
                answer[i + 1] = sessionnPtr[i];
        }
        catch (std::runtime_error const & err)
        {
            std::string errorMessage(err.what());
            answer = std::vector<char>(errorMessage.length());
            answer[0] = 0;
            for (size_t i = 0; i < errorMessage.length(); i++)
                answer[i + 1] = errorMessage[i];
        }
        return answer;
    }
    }
}
