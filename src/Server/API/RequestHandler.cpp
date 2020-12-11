#include "RequestHandler.h"

RequestHandler::RequestHandler()
{
    try
    {
    this->dataBase = std::unique_ptr<DataBaseObject>(new DataBaseObject);
    this->accountManager = std::unique_ptr<AccountManager>(new AccountManager(std::move(dataBase)));
    } catch (std::runtime_error const &err)
    {
        throw;
    }
}

std::vector<char> RequestHandler::handle(std::vector<char> buffer)
{
    std::vector<char> answer;
    switch (buffer[0]) {
    case 0:
        buffer.erase(buffer.begin());
        answer = userRegistration(buffer);
    default:
        break;
    }
    return answer;
}

//Only for test. In future it will be rewritted.
std::vector<char> RequestHandler::userRegistration(std::vector<char> buffer)
{
    RequestReader reader(std::make_shared<std::vector<char>>(buffer));
    RequestWritter writer;
    try{
            const std::string email = reader.read<std::string>();
            const std::string password = reader.read<std::string>();
            std::uint32_t sessionToken = accountManager->createAccount(email, password);
            writer.write<char>(1);
            writer.write<std::uint32_t>(sessionToken);
        }
        catch (std::runtime_error const & err)
        {
            std::string errorMessage(err.what());
            writer.write<char>(0);
            writer.write<std::string>(errorMessage);
        }

    auto responce = writer.getBuffer();
    return responce;
}
