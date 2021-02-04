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

std::vector<char> FilesRepository::readPartOfFile(std::uint32_t sessionToken)
{
    auto file = usingFiles.find(sessionToken);

    if (file == usingFiles.end())
        throw std::runtime_error("A file doesn`t exist");

    auto part = file->second.read();

    if (file->second.isEnded)
    {
        usingFiles.erase(file);
    }

    return part;
}

void FilesRepository::writePartOfFile(const std::vector<char> &buffer, std::uint32_t sessionToken)
{
    auto file = usingFiles.find(sessionToken);

    if (file == usingFiles.end())
        throw std::runtime_error("A file doesn`t exist");

    file->second.write(buffer);

    if (file->second.isEnded)
    {
        usingFiles.erase(file);
    }
}

void FilesRepository::deleteFile(std::uint32_t sessionToken)
{
    usingFiles[sessionToken].deleteFile();
    usingFiles.erase(sessionToken);
}
