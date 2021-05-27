#pragma once
#include <vector>

class ICrypter
{
public:
    virtual std::vector<char> crypt(std::vector<char> const &) = 0;
};
