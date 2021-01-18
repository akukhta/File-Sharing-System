#pragma once
#include <memory>
#include <vector>
#include <string>
#include <set>
#include <iterator>
#include "Data/databaseobject.h"
#include "Common/Node.h"

class NodesManager
{
public:
    NodesManager(std::shared_ptr<DataBaseObject> const & db);
    std::vector<std::pair<std::string, std::string>> getNodesList(std::uint32_t sessionToken, bool &success) const;
    std::uint32_t createNode(const std::uint32_t sessionToken, const std::string deletingDate);
    static constexpr std::uint32_t InvalidNodeID = 0;
private:
    //Pointer to database object
    std::shared_ptr<DataBaseObject> database;


    std::set<Node> nodesSet;

    //This can make Nodes' IDs generating fuction faster.
    //Basic algorithm:
    //1.Generate a random ID
    //2.Check an existing of this ID in the nodes set.
    //If the ID exists, we need to generate an another one and repeat this steep
    //This gives us O(n^2)
    //Extended algorihm:
    //1.Check a difference between ID[i] and ID[i + 1]
    //If this difference bigger than zero,
    //we can generate an unique ID in a distance from ID[i] + 1 to ID[i] + 1 + the difference.
    //This algorithm give us O(n), but we need an additional set with sorted nodes' IDs.

    std::set<std::uint32_t> nodesIDs;
    
    std::uint32_t generateID();
};
