#pragma once
#include <vector>
#include "Common/Node.h"

class AbstractNodesRepository
{

public:
    virtual std::vector<Node> getNodesList(std::uint32_t sessionToken, bool &success) const = 0;
    virtual std::uint32_t createNode(const std::uint32_t sessionToken, const std::string deletingDate) = 0;

    virtual ~AbstractNodesRepository()
    {
        ;
    }

};
