#include "FilesRepository.h"

FilesRepository::FilesRepository(std::shared_ptr<IDataBase> dataBase) : dataBase(dataBase)
{ ; }

void FilesRepository::startWritting(size_t nodeID, std::uint32_t sessionToken, const std::string &fileName, std::uint64_t fileSize)
{
    usingFiles.insert(std::make_pair(sessionToken, FileRepresentation(fileName, nodeID, Permissions::WriteOnly, fileSize)));
}

std::uint64_t FilesRepository::startReading(size_t nodeID, std::uint32_t sessionToken, const std::string &fileName)
{
    usingFiles.insert(std::make_pair(sessionToken, FileRepresentation(fileName, nodeID, Permissions::ReadOnly)));
    return usingFiles[sessionToken].getFileSize();
}

std::vector<unsigned char> FilesRepository::readPartOfFile(std::uint32_t sessionToken)
{
    return usingFiles[sessionToken].read();
}

void FilesRepository::writePartOfFile(const std::vector<unsigned char> &buffer, std::uint32_t sessionToken)
{
    usingFiles[sessionToken].write(buffer);
}

void FilesRepository::deleteFile(std::uint32_t sessionToken)
{
    usingFiles[sessionToken].deleteFile();
    usingFiles.erase(sessionToken);
}
