#pragma once
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iterator>
#include <cstdio>

enum class Permissions : bool { ReadOnly = false, WriteOnly = true};

class FileRepresentation
{
public:
    FileRepresentation(std::string const &fullFilePath, Permissions const permission, size_t nodeID = 0,std::uint64_t fileSize = 0);
    FileRepresentation() = default;
    std::vector<char> read();
    void write(std::vector<char> const & chunk);
    std::uint64_t getFileSize();
    void deleteFile();
    bool isDone = false;
private:
    std::string fullFilePath;
    std::filesystem::path pathToFile;
    std::fstream file;
    std::uint64_t fileSize;
    std::uint64_t currentPosition;
    Permissions permission;
    const size_t chunkSize = 64;
    void closeFile();
};

