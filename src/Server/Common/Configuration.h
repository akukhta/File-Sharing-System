#pragma once
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

class Configuration
{
public:
    Configuration() = delete;
    std::string static getDefaultIP();
    int static getDafultPort();
    std::string static getDefaultPathDB();
    std::string static getDefaultDBServer();
    std::string static getDefaultDBUser();
    std::string static getDefaultDBPassword();
    std::string static getDefaultDB();
    std::string static getDefaultUserDB();
    std::string static getDefaultPassDB();
    std::string static getCurrentTimeAsStdString();
    std::string static getServerErrorMessage();
};

