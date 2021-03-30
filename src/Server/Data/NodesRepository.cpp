#include "NodesRepository.h"

NodesRepository::NodesRepository(std::shared_ptr<IDataBase> dataBase, std::weak_ptr<IFilesManager> filesManager)
    : dataBase(dataBase), filesManager(std::move(filesManager))
{
    auto allNodes = dataBase->allNodes();

    std::scoped_lock lock(nodesMutex, idsMutex);

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

    }

    catch (std::runtime_error const & err)
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

    try{

        auto res = dataBase->createNode(sessionToken, deletingDate, generatedNodeID);

        nodesMutex.lock();
        idsMutex.lock();
        nodesIDs.insert(generatedNodeID);
        nodesSet.insert(res);
        nodesMutex.unlock();
        idsMutex.unlock();

    }

    catch (std::runtime_error const & err)
    {
        return AbstractNodesRepository::InvalidNodeID;
    }

    return generatedNodeID;
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

void NodesRepository::deleteOverdueNodes()
{
    nodesMutex.lock();
    if (nodesSet.size() == 0)
    {
        nodesMutex.unlock();
        return;
    }

    auto nodeIterator = nodesSet.begin();
    nodesMutex.unlock();

    while (!nodeIterator->isAlive()) {
        std::lock_guard<std::mutex> lock(nodesMutex);

        if (!filesManager.expired())
        {
            auto filesManagerPtr = filesManager.lock();
            filesManagerPtr->deleteDirectory(std::to_string(nodeIterator->NodeID));
        }

        dataBase->deleteNode(nodeIterator->NodeID);
        nodesIDs.erase(nodeIterator->NodeID);
        nodesSet.erase(nodeIterator);

        if (nodesSet.size() == 0)
            break;

        nodeIterator = nodesSet.begin();
    }
}

