#pragma once
#include <unordered_map>
#include "Data/AbstractFilesRepository.h"
#include "Data/FileRepresentation.h"
#include "Data/IDataBase.h"

class FilesRepository : public AbstractFilesRepository
{
public:
    FilesRepository(std::shared_ptr<IDataBase> dataBase);
    virtual void startWritting(size_t nodeID, std::uint32_t sessionToken, std::string const & fileName, std::uint64_t fileSize) override final;
    virtual std::uint64_t startReading(size_t nodeID, std::uint32_t sessionToken, std::string const & fileName) override final;
    virtual std::vector<unsigned char> readPartOfFile(std::uint32_t sessionToken) override final;
    virtual void writePartOfFile(std::vector<unsigned char> const & buffer, std::uint32_t sessionToken) override final;
    virtual void deleteFile(std::uint32_t sessionToken) override final;
private:
    std::unordered_map<std::uint32_t, FileRepresentation> usingFiles;
    std::shared_ptr<IDataBase> dataBase;
};

