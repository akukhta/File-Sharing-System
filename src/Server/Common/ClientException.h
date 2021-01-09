#pragma once
#include <stdexcept>

class ClientException : public std::runtime_error
{
public:
    ClientException(std::string const &str) : std::runtime_error(str)
    { ; }
};
