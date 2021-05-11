#include "Crypter.h"

Crypter::Crypter()
{
    dllHandler = dlopen("libCryptoLib.so",  RTLD_LAZY);

    if (dllHandler == nullptr)
        throw std::runtime_error("Failed to load security dll!");

    getInstance = reinterpret_cast<void* (*) (std::string)>(dlsym(dllHandler, "getInstance"));
    crypt = reinterpret_cast<std::vector<char> (*) (void *, std::vector<char> const &)>(dlsym(dllHandler,
                                                                                              "crypt"));
}

void Crypter::registerUserToCrypter(uint32_t sessionToken, std::string email)
{
    loadedCrypters.insert(std::make_pair(sessionToken, getInstance(email)));
}

std::vector<char> Crypter::cryptBuffer(std::uint32_t sessionToken , const std::vector<char> &buffer)
{
    return crypt(loadedCrypters[sessionToken], buffer);
}
