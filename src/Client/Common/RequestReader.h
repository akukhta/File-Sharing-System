#pragma once
#include <memory>
#include <vector>
#include <type_traits>
#include <iostream>
#include "Common/ServerResults.h"

class RequestReader
{
public:
    RequestReader(std::vector<char> const & buffer): currentOffset(0),
        buffer(buffer)
    { ; }

    template<class T,typename std::enable_if_t<std::is_fundamental<T>::value>* = nullptr>
    T read()
    {
        if (currentOffset + sizeof(T) > buffer.size())
        {
            throw std::runtime_error("Cannot get a parameter");
        }

        std::vector<char> subbuffer(buffer.begin() + currentOffset, buffer.begin() + currentOffset + sizeof(T));
        T result = *reinterpret_cast<T*>(subbuffer.data());
        currentOffset += sizeof(T);
        return result;
    }

    template<class T, typename std::enable_if_t<std::is_same<ServerResult,T>::value>* = nullptr>
    ServerResult read()
    {
        return read<char>() == 0 ? ServerResult::Failure : ServerResult::Success;
    }

    template<class T, typename std::enable_if_t<std::is_same<std::vector<char>,T>::value>* = nullptr>
    std::vector<char> read()
    {

        if (currentOffset + sizeof(size_t) > buffer.size())
        {
            throw std::runtime_error("Cannot get a parameter");
        }

        std::vector<char> sizeBuffer(buffer.begin() + currentOffset, buffer.begin() + currentOffset + sizeof(size_t));
        size_t blockSize = *reinterpret_cast<size_t*>(sizeBuffer.data());
        currentOffset += sizeof(size_t);
        
        if (blockSize > buffer.size() - currentOffset)
        {
            throw std::runtime_error("Wrong buffer size!");
        }

        std::vector<char> result(buffer.begin() + currentOffset, buffer.begin() + currentOffset + blockSize);
        currentOffset += blockSize;
        return result;
    }

    template<class T, typename std::enable_if_t<std::is_same<std::string,T>::value>* = nullptr>
    std::string read()
    {

        if (currentOffset + sizeof(size_t) > buffer.size())
        {
            throw std::runtime_error("Cannot get a parameter");
        }

        std::vector<char> sizeBuffer(buffer.begin() + currentOffset, buffer.begin() + currentOffset + sizeof(size_t));
        size_t blockSize = *reinterpret_cast<size_t*>(sizeBuffer.data());
        currentOffset += sizeof(size_t);

        if (blockSize > buffer.size() - currentOffset)
        {
            throw std::runtime_error("Wrong buffer size!");
        }

        std::string result(buffer.begin() + currentOffset, buffer.begin() + currentOffset + blockSize);
        currentOffset += blockSize;
        return result;
    }

private:
    size_t currentOffset;
    std::vector<char> const & buffer;
};

