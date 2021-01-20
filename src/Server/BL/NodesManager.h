#pragma once
#include <memory>
#include <vector>
#include <string>
#include <set>
#include <iterator>
#include "Common/AbstractNodesRepository.h"
#include "Data/databaseobject.h"
#include "Common/Node.h"

class NodesManager
{
public:
    NodesManager(std::unique_ptr<AbstractNodesRepository> & nodesRepository);
    std::vector<std::pair<std::string, std::string>> getNodesList(std::uint32_t sessionToken) const;
    std::uint32_t createNode(const std::uint32_t sessionToken, const std::string deletingDate);

private:

    std::unique_ptr<AbstractNodesRepository> nodesRepository;
};
