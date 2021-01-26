#pragma once
#include <memory>
#include <mutex>
#include "Data/AbstractNodesRepository.h"
#include "Data/IDataBase.h"
#include "Common/Node.h"
#include "Common/Logger.h"

class NodesRepository : public AbstractNodesRepository
{

public:

    NodesRepository(std::shared_ptr<IDataBase> dataBase);

    virtual std::vector<std::pair<std::string,std::string>> getNodesList(std::uint32_t sessionToken, bool &success) const override final;
    virtual std::uint32_t createNode(const std::uint32_t sessionToken, const std::string deletingDate) override final;
    virtual void deleteOverdueNodes() override final;

    ~NodesRepository()
    {
        Logger::log()->debugMessage("The nodes repository has been deleted!");
    }

private:

    std::shared_ptr<IDataBase> dataBase;
    std::multiset<Node> nodesSet;
    std::set<std::uint32_t> nodesIDs;
    std::mutex nodesMutex, idsMutex;

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

    std::uint32_t generateID();

};

