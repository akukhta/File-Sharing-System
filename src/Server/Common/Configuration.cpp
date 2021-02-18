#include "Configuration.h"

std::string Configuration::getDefaultIP()
{
    return "127.0.0.1";
}

int Configuration::getDafultPort()
{
    return 5441;
}

std::string Configuration::getDefaultPathDB()
{
    return "127.0.0.1";
}

std::string Configuration::getDefaultUserDB()
{
    return "root";
}
std::string Configuration::getDefaultPassDB()
{
    return "root";
}

std::string Configuration::getCurrentTimeAsStdString()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Configuration::getServerErrorMessage()
{
    return "Internal server error occurred";
}

std::string Configuration::getDefaultDBServer()
{
    return "localhost";
}

std::string Configuration::getDefaultDBUser()
{
    return "root";
}

std::string Configuration::getDefaultDBPassword()
{
    return "root";
}

std::string Configuration::getDefaultDB()
{
    return "FileSharingSystem";
}
