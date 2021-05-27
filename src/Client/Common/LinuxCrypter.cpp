#include "LinuxCrypter.h"

LinuxCrypter::LinuxCrypter(std::string email)
{
    dllHandler = dlopen("./libCryptoLib.so",  RTLD_LAZY);

    if (dllHandler == nullptr)
    {
        throw std::runtime_error("Failed to load security dll!");
    }

    getInstance = reinterpret_cast<void* (*) (std::string)>(dlsym(dllHandler, "getInstance"));

    if (!getInstance)
    {
        throw std::runtime_error("Failed to find getInstance sym!");
    }

    _crypt = reinterpret_cast<std::vector<char> (*) (void *, std::vector<char> const &)>(dlsym(dllHandler,
        "crypt"));

    if (!_crypt)
    {
        throw std::runtime_error("Failed to find crypt sym!");
    }

    loadedCrypter = getInstance(email);

    if (loadedCrypter == nullptr)
    {
        throw std::runtime_error("Crypter object hasn`t created!");
    }
}

std::vector<char> LinuxCrypter::crypt(const std::vector<char> & buffer)
{
    return _crypt(loadedCrypter, buffer);
}
