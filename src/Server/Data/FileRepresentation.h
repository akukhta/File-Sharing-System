#pragma once
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iterator>

enum class Permissions : bool { ReadOnly = false, WriteOnly = true};

class FileRepresentation
{
public:
    FileRepresentation(std::string const &fileName, size_t nodeID, std::uint64_t const fileSize,
                       Permissions const permission);

    const std::vector<unsigned char> read();
    void write(std::vector<unsigned char> const & chunk);

private:
    std::string const fileName;
    std::fstream file;
    std::uint64_t const fileSize;
    std::uint64_t currentPosition;
    std::chrono::time_point<std::chrono::system_clock> lastUsed;
    Permissions const permission;
    const size_t chunkSize = 64;
};

