#include "FilesRepository.h"

FilesRepository::FilesRepository(std::shared_ptr<IDataBase> dataBase) : dataBase(dataBase)
{ ; }

void FilesRepository::startWritting(std::uint32_t nodeID, std::uint32_t sessionToken, const std::string &fileName, std::uint64_t fileSize)
{
    dataBase->addFile(nodeID, fileName);
    usingFiles.insert(std::make_pair(sessionToken, FileRepresentation(fileName, nodeID, Permissions::WriteOnly, fileSize)));
}

std::uint64_t FilesRepository::startReading(std::uint32_t nodeID, std::uint32_t sessionToken, const std::string &fileName)
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

void FilesRepository::deleteDirectory(const std::string &dirName)
{
    std::filesystem::remove_all(dirName);
}

void FilesRepository::deleteFile(std::uint32_t nodeID, const std::string &fileName)
{
    if(std::filesystem::remove(std::to_string(nodeID) +
        std::filesystem::path::preferred_separator + fileName))
    {
        dataBase->deleteFile(nodeID, fileName);
    }
    else
    {
        throw std::runtime_error(fileName + " has not deleted!");
    }
}

std::vector<std::string> FilesRepository::getFilesList(std::uint32_t nodeID)
{
    return dataBase->getFilesList(nodeID);
}
