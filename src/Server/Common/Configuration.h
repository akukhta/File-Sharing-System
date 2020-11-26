#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <string>

class Configuration
{
public:
    Configuration() = delete;
    std::string static getDefaultIP();
    int static getDafultPort();
    std::string static getDefaultPathDB();
};

#endif // CONFIGURATION_H
