#include "NodesManager.h"

NodesManager::NodesManager(std::unique_ptr<AbstractNodesRepository> & nodesRepository)
    : nodesRepository(std::move(nodesRepository))
{

}

std::vector<std::pair<std::string, std::string>> NodesManager::getNodesList(std::uint32_t sessionToken) const
{
    bool success;
    auto answer = nodesRepository->getNodesList(sessionToken, success);

    if (!success)
        throw std::runtime_error("Couldn`t get nodes list!");

    return answer;
}

std::uint32_t NodesManager::createNode(const std::uint32_t sessionToken, const std::string deletingDate)
{
    return nodesRepository->createNode(sessionToken, deletingDate);
}
