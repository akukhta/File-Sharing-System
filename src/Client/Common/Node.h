#pragma once
#include <vector>
#include <string>

class Node
{
public:
    Node(std::string const &nodeID, std::string const &deletingDate) : nodeID(nodeID),
        deletingDate(deletingDate)
    { }

    Node(Node const& node)
    {
        nodeID = node.nodeID;
        deletingDate = node.deletingDate;
        itemsIsLoaded = node.itemsIsLoaded;
        fileNames = node.fileNames;
    }

    virtual ~Node() = default;

    Node(Node && node) noexcept
    {
       std::swap(nodeID, node.nodeID);
       std::swap(deletingDate, node.deletingDate);
       itemsIsLoaded = node.itemsIsLoaded;
       std::swap(fileNames, node.fileNames);
    }

    bool itemsIsLoaded = false;
    std::string nodeID, deletingDate;
    std::vector<std::string> fileNames;
};

