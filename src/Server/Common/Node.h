#pragma once
#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>

class Node
{
public:
    Node(int NodeID, std::string const & deletingTimeStr);
    bool operator<(Node const &node) const;
    bool operator>(Node const &node) const;
    bool isAlive() const;

    const int NodeID;
private:
    std::chrono::time_point<std::chrono::system_clock> deletingTime;
    long long minutesLeft() const;

#ifdef _WIN32
     char* strptime(const char* s, const char* f, struct tm* tm);
#endif
};

