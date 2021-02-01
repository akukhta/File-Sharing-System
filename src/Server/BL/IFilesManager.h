#pragma once
#include <string>
#include <vector>

class IFilesManager
{
public:
    IFilesManager() = default;
    virtual void startWritting(size_t nodeID, std::uint32_t sessionToken, std::string const & fileName, std::uint64_t fileSize) = 0;
    virtual std::uint64_t startReading(size_t nodeID, std::uint32_t sessionToken, std::string const & fileName) = 0;
    virtual std::vector<unsigned char> readPartOfFile(std::uint32_t sessionToken) = 0;
    virtual void writePartOfFile(std::vector<unsigned char> const & buffer, std::uint32_t sessionToken) = 0;
    virtual void deleteFile(std::uint32_t sessionToken) = 0;
    virtual ~IFilesManager() = default;
};
