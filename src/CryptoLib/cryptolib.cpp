#include "cryptolib.h"

CryptoLib::CryptoLib(std::string Seed)
{
    currentSeed = std::hash<std::string>()(Seed);
    std::cout << "Current seed for " << Seed << " is " << currentSeed << std::endl;
    srand(currentSeed);
}

std::vector<char> CryptoLib::crypt(const std::vector<char> &buffer) const
{
      std::vector<char> decoded;

      for (auto x : buffer)
          decoded.push_back(x ^ static_cast<char>(rand()));

      return decoded;
}

