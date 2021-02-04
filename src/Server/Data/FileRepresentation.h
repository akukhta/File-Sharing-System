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
    FileRepresentation(std::string const &fileName, size_t nodeID, Permissions const permission, std::uint64_t const fileSize = 0);
    FileRepresentation() = default;
    std::vector<char> read();
    void write(std::vector<char> const & chunk);
    std::uint64_t getFileSize();
    void deleteFile();
    bool isEnded = false;
private:
    std::string fileName;
    std::filesystem::path pathToFile;
    std::fstream file;
    std::uint64_t fileSize;
    std::uint64_t currentPosition;
    std::chrono::time_point<std::chrono::system_clock> lastUsed;
    Permissions permission;
    const size_t chunkSize = 64;
};

