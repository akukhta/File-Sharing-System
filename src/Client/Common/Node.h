#pragma once
#include <vector>
#include <string>

class Node
{
public:
    Node(std::string nodeID) : nodeID(nodeID) { ; };
    bool itemsIsLoaded = false;
    std::string nodeID;
    std::vector<std::string> items;
};

