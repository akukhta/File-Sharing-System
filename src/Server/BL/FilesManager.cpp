#include "FilesManager.h"

FilesManager::FilesManager(std::unique_ptr<AbstractFilesRepository> filesRep) :
    filesRep(std::move(filesRep))
{;}

void FilesManager::startWritting(size_t nodeID, std::uint32_t sessionToken, const std::string &fileName, std::uint64_t fileSize)
{
    filesRep->startWritting(nodeID, sessionToken, fileName, fileSize);
}

std::uint64_t FilesManager::startReading(size_t nodeID, std::uint32_t sessionToken, std::string const & fileName)
{
    return filesRep->startReading(nodeID, sessionToken, fileName);
}

std::vector<unsigned char> FilesManager::readPartOfFile(std::uint32_t sessionToken)
{
    return filesRep->readPartOfFile(sessionToken);
}

void FilesManager::writePartOfFile(const std::vector<unsigned char> &buffer, std::uint32_t sessionToken)
{
    filesRep->writePartOfFile(buffer, sessionToken);
}

void FilesManager::deleteFile(std::uint32_t sessionToken)
{
    filesRep->deleteFile(sessionToken);
}
