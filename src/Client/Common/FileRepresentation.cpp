#include "FileRepresentation.h"

FileRepresentation::FileRepresentation(std::string const &fileName, size_t nodeID, Permissions const permission, std::uint64_t const fileSize) : fileName(fileName), fileSize(fileSize), permission(permission)
{
    std::filesystem::path directoryPath(std::to_string(nodeID));
    //If we need a file for writing
    if (permission == Permissions::WriteOnly)
    {
        //Checking if a directory with the name same as node id exists
        if (!std::filesystem::exists(directoryPath))
        {
            //create if the directory doesn`t exist
            std::filesystem::create_directory(directoryPath);
        }
        pathToFile = directoryPath / fileName;
        file.open(pathToFile, file.binary | file.in);
    }

    else
    {
        this->fileSize = static_cast<std::uint64_t>(std::filesystem::file_size(directoryPath / fileName));
        pathToFile = directoryPath / fileName;
        file.open(pathToFile, file.binary | file.out);
    }

    if (!file.is_open())
        throw std::runtime_error("Couldn`t open a file!");

}

const std::vector<unsigned char> FileRepresentation::read()
{
    if (permission == Permissions::WriteOnly)
        throw std::runtime_error("A file has a read only attribute!");
    if (currentPosition == fileSize)
        throw std::runtime_error("A file has been readed till the end!");

    std::uint64_t diff = fileSize - currentPosition;
    size_t currentChunkSize = diff >= chunkSize ? chunkSize : diff;

    std::vector<unsigned char> chunk;
    std::copy_n(std::istream_iterator<unsigned char>(file), currentChunkSize, std::back_inserter(chunk));

    currentPosition += currentChunkSize;


    return chunk;
}

void FileRepresentation::write(const std::vector<unsigned char> &chunk)
{
    if (permission == Permissions::ReadOnly)
        throw std::runtime_error("A file has a ReadOnly permission");

    if (currentPosition >= fileSize)
        throw std::runtime_error("A file has been ended");

    std::copy(chunk.begin(), chunk.end(), std::ostream_iterator<unsigned char>(file));

    currentPosition += chunk.size();


}

std::uint64_t FileRepresentation::getFileSize()
{
    return this->fileSize;
}

void FileRepresentation::deleteFile()
{
    std::remove(pathToFile.c_str());
}



