#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Data/databaseobject.h"

class NodesManager
{
public:
    NodesManager(std::shared_ptr<DataBaseObject> db);
    std::vector<std::string> getNodesList(unsigned int sessionToken, bool &success);
private:
    //Pointer to database object
    std::shared_ptr<DataBaseObject> database;
};
