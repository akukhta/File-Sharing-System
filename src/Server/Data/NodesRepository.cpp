#include "NodesRepository.h"

NodesRepository::NodesRepository(std::shared_ptr<DataBaseObject> const & dataBase)
    : dataBase(dataBase)
{
    auto allNodes = dataBase->allNodes();
    nodesSet = allNodes.first;
    nodesIDs = allNodes.second;
}

std::vector<std::pair<std::string,std::string>> NodesRepository::getNodesList(std::uint32_t sessionToken, bool &success) const
{
    if (!dataBase)
        throw std::runtime_error("Database wasn't initialized");

    success = true; // Just for test.

    std::vector<std::pair<std::string,std::string>> result;
    try{
        result = dataBase->nodesQuery(sessionToken);
    } catch (std::runtime_error const & err)
    {
        success = false;
    }

    return result;
}



std::uint32_t NodesRepository::createNode(const std::uint32_t sessionToken, const std::string deletingDate)
{
    if (!dataBase)
        throw std::runtime_error("Database wasn't initialized");

    std::uint32_t generatedNodeID = generateID();

    if (!generatedNodeID)
        return  AbstractNodesRepository::InvalidNodeID;

    auto res = dataBase->createNode(sessionToken, deletingDate, generatedNodeID);

    if (res)
    {
        nodesIDs.insert(generatedNodeID);
    }

    return res ? generatedNodeID : AbstractNodesRepository::InvalidNodeID;
}

std::uint32_t  NodesRepository::generateID()
{
    if (nodesIDs.size() < 2)
        return rand() + 1; // If nodes' set contains too few elements

    else
    {
        for (auto currNodeIter = nodesIDs.begin(); currNodeIter != --nodesIDs.end();)
        {
            int currID = *currNodeIter, nextID = *(++currNodeIter);
            if (nextID - currID > 1)
            {
                return rand() % (nextID  - currID - 1) + currID + 1; //Smart (i hope) generation
            }
        }

        if (*nodesIDs.end() != std::uint32_t{0xFFFFFFFF})
            nodesIDs.insert(rand() + *nodesIDs.end() + 1);
    }

    return AbstractNodesRepository::InvalidNodeID; //Couldn`t generate a new node`s ID
}

