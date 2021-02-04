#pragma once
#include <memory>
#include "BL/IFilesManager.h"
#include "Data/AbstractFilesRepository.h"

class FilesManager : public IFilesManager
{
public:
    FilesManager(std::unique_ptr<AbstractFilesRepository> filesRep);
    virtual std::vector<std::string> getFilesList(std::uint32_t nodeID) override final;
    virtual void startWritting(std::uint32_t nodeID, std::uint32_t sessionToken, std::string const & fileName, std::uint64_t fileSize) override final;
    virtual std::uint64_t startReading(std::uint32_t nodeID, std::uint32_t sessionToken, std::string const & fileName) override final;
    virtual std::vector<char> readPartOfFile(std::uint32_t sessionToken) override final;
    virtual void writePartOfFile(std::vector<char> const & buffer, std::uint32_t sessionToken) override final;
    virtual void deleteFile(std::uint32_t sessionToken) override final;
private:
    std::unique_ptr<AbstractFilesRepository> filesRep;
};


