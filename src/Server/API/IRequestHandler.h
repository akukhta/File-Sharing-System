#pragma once
#include <vector>

class IRequestHandler
{
public:

    IRequestHandler() = default;
    virtual std::vector<char> handle(std::vector<char> &buffer, int socketFD) = 0;
    virtual void destroySession(int socketFD) = 0;
    ~IRequestHandler() = default;
};
