#pragma once
#include <string>

class EMailManager
{
public:
    //Method for message sending to user
    static void Send(std::string const & to, std::string const &subject, std::string const &message);
};

