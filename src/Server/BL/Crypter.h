#pragma once
#include <unordered_map>
#include <memory>
#include <functional>
#include <dlfcn.h>

class Crypter
{
public:
    Crypter();
    void registerUserToCrypter(std::uint32_t sessionToken, std::string email);
    std::vector<char> cryptBuffer(std::uint32_t sessionToken, std::vector<char> const & buffer);

private:

// Custom deleter for unique_ptr, but it doesn't work
//    static constexpr auto voidDeleter = [](void * const data) {
//         int const *pointer = static_cast<int const*>(data);
//         delete pointer;
//    };

//    std::unordered_map<std::uint32_t, std::unique_ptr<void, decltype(voidDeleter)>> loadedCrypters;

    std::unordered_map<std::uint32_t, void *> loadedCrypters;
    void *dllHandler = nullptr;
    std::function<void* (std::string)> getInstance;
    std::function<std::vector<char> (void *, std::vector<char> const &)> crypt;
};


