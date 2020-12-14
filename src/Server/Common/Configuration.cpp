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
