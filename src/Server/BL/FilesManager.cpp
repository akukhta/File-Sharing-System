#include "FilesManager.h"

FilesManager::FilesManager(std::unique_ptr<AbstractFilesRepository> filesRep) :
    filesRep(std::move(filesRep))
{;}

void FilesManager::startWritting(std::uint32_t nodeID, std::uint32_t sessionToken, const std::string &fileName, std::uint64_t fileSize)
{
    filesRep->startWritting(nodeID, sessionToken, fileName, fileSize);
}

std::uint64_t FilesManager::startReading(std::uint32_t nodeID, std::uint32_t sessionToken, std::string const & fileName)
{
    return filesRep->startReading(nodeID, sessionToken, fileName);
}

std::vector<char> FilesManager::readPartOfFile(std::uint32_t sessionToken)
{
    return filesRep->readPartOfFile(sessionToken);
}

void FilesManager::writePartOfFile(const std::vector<char> &buffer, std::uint32_t sessionToken)
{
    filesRep->writePartOfFile(buffer, sessionToken);
}

void FilesManager::deleteDirectory(const std::string &dirName)
{
    filesRep->deleteDirectory(dirName);
}

std::vector<std::string> FilesManager::getFilesList(std::uint32_t nodeID)
{
    return filesRep->getFilesList(nodeID);
}
