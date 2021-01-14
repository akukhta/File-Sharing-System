#pragma once
#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>

class Node
{
public:
    Node(int NodeID, std::string const & creationTimeStr, long long lifeTimeInMins);
    bool operator<(Node const &node) const;
    bool operator>(Node const &node) const;
    bool isAlive() const;

private:
    const int NodeID;
    std::chrono::time_point<std::chrono::system_clock> creationTime;
    long long lifeTimeInMins;
    long long minutesLeft() const;

#ifdef _WIN32
     char* strptime(const char* s, const char* f, struct tm* tm);
#endif
};

