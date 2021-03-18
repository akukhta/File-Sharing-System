#include "FileRepresentation.h"

FileRepresentation::FileRepresentation(std::string const &fullFilePath,
    Permissions const permission, size_t nodeID, std::uint64_t fileSize,
    std::string const & destFolderName) : fullFilePath(fullFilePath), fileSize(fileSize), permission(permission)
{
    pathToFile = fullFilePath;

    //If we need a file for writing
    if (permission == Permissions::WriteOnly)
    {
        pathToFile = destFolderName + std::filesystem::path::preferred_separator + fullFilePath;
        file.open(pathToFile.string(), std::fstream::out | std::fstream::binary);
    }

    else
    {
        this->fileSize = static_cast<std::uint64_t>(std::filesystem::file_size(fullFilePath));
        file.open(pathToFile, file.binary | file.in);
    }

    if (!file.is_open() && permission == Permissions::ReadOnly)
        throw std::runtime_error("Couldn`t open a file!");

    currentPosition = 0;

}

std::vector<char> FileRepresentation::read()
{
    if (permission == Permissions::WriteOnly)
        throw std::runtime_error("A file has a read only attribute!");
    if (currentPosition == fileSize)
        throw std::runtime_error("A file has been readed till the end!");

    std::uint64_t diff = fileSize - currentPosition;
    size_t currentChunkSize = diff >= chunkSize ? chunkSize : diff;

    std::vector<char> chunk(currentChunkSize);
    file.read(chunk.data(), currentChunkSize);

    currentPosition += currentChunkSize;

    if (currentPosition == fileSize)
        isDone = true;

    return chunk;
}

void FileRepresentation::write(const std::vector<char> &chunk)
{
    if (permission == Permissions::ReadOnly)
        throw std::runtime_error("A file has a ReadOnly permission");

    if (currentPosition >= fileSize)
        throw std::runtime_error("A file has been ended");

    file.write(chunk.data(), chunk.size());

    currentPosition += chunk.size();

    if (currentPosition == fileSize)
    {
        isDone = true;
    }
}

std::uint64_t FileRepresentation::getFileSize()
{
    return this->fileSize;
}

void FileRepresentation::deleteFile()
{
    std::remove(pathToFile.c_str());
}

void FileRepresentation::closeFile()
{
    file.close();
}



