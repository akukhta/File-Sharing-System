#ifndef EMAILMANAGER_H
#define EMAILMANAGER_H
#include <string>

class EMailManager
{
public:
    static void Send(std::string const & to, std::string const &subject, std::string const &message);
};

#endif // EMAILMANAGER_H
