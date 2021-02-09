#pragma once
#include <string>
#include <vector>

class AbstractFilesRepository
{
public:

    virtual void startWritting(std::uint32_t nodeID, std::uint32_t sessionToken, std::string const & fileName, std::uint64_t fileSize) = 0;
    virtual std::vector<std::string> getFilesList(std::uint32_t nodeID) = 0;
    virtual std::uint64_t startReading(std::uint32_t nodeID, std::uint32_t sessionToken, std::string const & fileName) = 0;
    virtual std::vector<char> readPartOfFile(std::uint32_t sessionToken) = 0;
    virtual void writePartOfFile(std::vector<char> const & buffer, std::uint32_t sessionToken) = 0;
    virtual void deleteDirectory(std::string const & dirName) = 0;
    virtual ~AbstractFilesRepository()
    {
        ;
    }
};
