#pragma once
#include <string>

class Configuration
{
public:
    Configuration() = delete;
    std::string static getDefaultIP();
    int static getDafultPort();
    std::string static getDefaultPathDB();
};

