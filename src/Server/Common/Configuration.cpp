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
     return "/home/alex/build-serverTEESTT-Desktop-Debug/users.db";
}
