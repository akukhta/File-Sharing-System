#include "Crypter.h"
#include <iostream>

Crypter::Crypter()
{
    dllHandler = dlopen("./libCryptoLib.so",  RTLD_LAZY);

    if (dllHandler == nullptr)
        throw std::runtime_error("Failed to load security dll!");

    getInstance = reinterpret_cast<void* (*) (std::string)>(dlsym(dllHandler, "getInstance"));
    crypt = reinterpret_cast<std::vector<char> (*) (void *, std::vector<char> const &)>(dlsym(dllHandler,
        "crypt"));
}

void Crypter::registerUserToCrypter(int sockfd, std::string email)
{
    loadedCrypters.insert(std::make_pair(sockfd, getInstance(email)));
}

std::vector<char> Crypter::cryptBuffer(int sockfd , const std::vector<char> &buffer)
{
    if (loadedCrypters.find(sockfd) == loadedCrypters.end())
        throw std::runtime_error("The client with " + std::to_string(sockfd) +
            " socket's descriptor hasn't registered");

    return crypt(loadedCrypters[sockfd], buffer);
}
