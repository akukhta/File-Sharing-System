#include "NodesManager.h"

NodesManager::NodesManager(std::shared_ptr<DataBaseObject> db) : database(db)
{
    ;
}

std::vector<std::string> NodesManager::getNodesList(unsigned int sessionToken, bool &success)
{
    if (!database)
        throw std::runtime_error("Database wasn't initialized");

    success = true; // Just for test.

    std::vector<std::string> result;
    try{
        result = database->nodesQuery(sessionToken);
    } catch (std::runtime_error const & err)
    {
        success = false;
    }

    return result;
}
