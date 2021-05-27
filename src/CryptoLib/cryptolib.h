#pragma once
#include <string>
#include <functional>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "CryptoLib_global.h"

class CRYPTOLIB_EXPORT CryptoLib
{
public:
    CryptoLib(std::string Seed);
    std::vector<char> crypt(std::vector<char> const & buffer) const;
private:
    std::uint64_t currentSeed;
};

#ifdef __cplusplus
extern "C" CRYPTOLIB_EXPORT void* getInstance(std::string seed)
#else
CRYPTOLIB_EXPORT void* getInstance(std::string seed)
#endif
{
    return new CryptoLib(seed);
}

#ifdef __cplusplus
extern "C" CRYPTOLIB_EXPORT std::vector<char> crypt(void const * object, std::vector<char> const & buffer)
#else
CRYPTOLIB_EXPORT std::vector<char> crypt(void const * object, std::vector<char> const & buffer)
#endif
{
    return static_cast<CryptoLib const *>(object)->crypt(buffer);
}

