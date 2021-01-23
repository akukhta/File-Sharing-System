#pragma once
#include <string>
#include <vector>

class INodesManager
{
public:
    virtual ~INodesManager() = default;
    virtual std::vector<std::pair<std::string, std::string>> getNodesList(std::uint32_t sessionToken) const = 0;
    virtual std::uint32_t createNode(const std::uint32_t sessionToken, const std::string deletingDate) = 0;
    virtual void startOverdueNodesDeleting() = 0;
};
