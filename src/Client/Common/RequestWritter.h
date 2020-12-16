#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <type_traits>

class RequestWritter
{
public:
    RequestWritter() = default;

     template<class T,typename std::enable_if_t<std::is_fundamental<T>::value>* = nullptr>
     void write(T const & arg)
     {
        char const *dataPtr = reinterpret_cast<char const *>(&arg);
        std::copy(dataPtr, dataPtr + sizeof(T), std::back_inserter(buffer));
     }

     template<class T, typename std::enable_if_t<std::is_same<std::vector<char>,T>::value>* = nullptr>
     void write(std::vector<char> const &arg)
     {
         write<size_t>(arg.size());
         std::copy(arg.begin(), arg.end(), std::back_inserter(buffer));
     }

     template<class T, typename std::enable_if_t<std::is_same<std::string,T>::value>* = nullptr>
     void write(std::string const& arg)
     {
        write<size_t>(arg.size());
        std::copy(arg.begin(), arg.end(), std::back_inserter(buffer));
     }

     const std::vector<char>& getBuffer()
     {
         return buffer;
     }

private:
     std::vector<char> buffer;
};

