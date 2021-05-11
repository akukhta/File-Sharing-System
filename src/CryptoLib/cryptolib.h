#pragma once
#include <string>
#include <functional>
#include <vector>
#include <cstdlib>
#include "CryptoLib_global.h"

class CRYPTOLIB_EXPORT CryptoLib
{
public:
    CryptoLib(std::string Seed);
    std::vector<char> crypt(std::vector<char> const & buffer) const;
private:
    std::uint64_t currentSeed;
};

extern void* getInstance(std::string seed)
{
    return new CryptoLib(seed);
}

extern std::vector<char> crypt(void const * object, std::vector<char> const & buffer)
{
    return static_cast<CryptoLib const *>(object)->crypt(buffer);
}
