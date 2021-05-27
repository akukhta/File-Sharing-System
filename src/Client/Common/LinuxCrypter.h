#pragma once
#include <string>
#include <functional>
#include <dlfcn.h>
#include "ICrypter.h"


class LinuxCrypter: public ICrypter
{
public:
    LinuxCrypter(std::string email);
    virtual std::vector<char> crypt(const std::vector<char> & buffer) override final;
private:
    void *dllHandler = nullptr;
    std::function<void* (std::string)> getInstance;
    std::function<std::vector<char> (void *, std::vector<char> const &)> _crypt;
    void *loadedCrypter = nullptr;
};


