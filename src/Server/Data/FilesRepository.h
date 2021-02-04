#pragma once
#include <unordered_map>
#include "Data/AbstractFilesRepository.h"
#include "Data/FileRepresentation.h"
#include "Data/IDataBase.h"

class FilesRepository : public AbstractFilesRepository
{
public:
    FilesRepository(std::shared_ptr<IDataBase> dataBase);
    virtual std::vector<std::string> getFilesList(std::uint32_t nodeID) override final;
    virtual void startWritting(std::uint32_t nodeID, std::uint32_t sessionToken, std::string const & fileName, std::uint64_t fileSize) override final;
    virtual std::uint64_t startReading(std::uint32_t nodeID, std::uint32_t sessionToken, std::string const & fileName) override final;
    virtual std::vector<char> readPartOfFile(std::uint32_t sessionToken) override final;
    virtual void writePartOfFile(std::vector<char> const & buffer, std::uint32_t sessionToken) override final;
    virtual void deleteFile(std::uint32_t sessionToken) override final;
private:
    std::unordered_map<std::uint32_t, FileRepresentation> usingFiles;
    std::shared_ptr<IDataBase> dataBase;
};

