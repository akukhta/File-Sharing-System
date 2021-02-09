#pragma once
#include <mutex>
#include <memory>
#include <vector>
#include <string>
#include <set>
#include <iterator>
#include <thread>
#include <atomic>
#include "BL/INodesManager.h"
#include "BL/IFilesManager.h"
#include "Data/AbstractNodesRepository.h"
#include "Common/Node.h"

class NodesManager : public INodesManager
{
public:
    NodesManager(std::unique_ptr<AbstractNodesRepository> nodesRepository, std::weak_ptr<IFilesManager> filesManager);
    virtual std::vector<std::pair<std::string, std::string>> getNodesList(std::uint32_t sessionToken) const override final;
    virtual std::uint32_t createNode(const std::uint32_t sessionToken, const std::string deletingDate) override final;
    virtual void startOverdueNodesDeleting() override final;

    ~NodesManager()
    {
        objIsAlive = false;
        std::cout << "Nodes manager has been deleted!" << std::endl;
    }

private:
    std::unique_ptr<AbstractNodesRepository> nodesRepository;
    std::weak_ptr<IFilesManager> filesManager;
    void overdueNodesDeleting();

    std::atomic<bool> objIsAlive = true;

    //Once a minute
    const std::chrono::seconds nodesCheckingFrequency{30};
};
