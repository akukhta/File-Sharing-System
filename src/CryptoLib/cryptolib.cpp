#include "cryptolib.h"

CryptoLib::CryptoLib(std::string Seed)
{
    currentSeed = std::hash<std::string>()(Seed);
    std::cout << "CryptoLib Objet has been created!" << std::endl;
    randomGenerator.seed(currentSeed);
}

std::vector<char> CryptoLib::crypt(const std::vector<unsigned char> &buffer)
{
      std::vector<char> decoded;

      for (auto x : buffer)
      {
          char gamma = static_cast<unsigned char>(randomGenerator());
          decoded.push_back(static_cast<unsigned char>(x ^ gamma));
      }
      return decoded;
}

