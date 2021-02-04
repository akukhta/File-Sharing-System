#pragma once
#include <vector>
#include <set>
#include "Common/Node.h"

class IDataBase
{
public:

    IDataBase() = default;
    virtual bool insertQuery(std::string querystr) = 0;
    virtual bool authorizationQuery(std::string const & email, std::string const & password, size_t &userID) = 0;
    virtual bool createSessionQuery(std::uint32_t sessionToken, int socketID, int userID) = 0;
    virtual Node createNode(const std::uint32_t sessionToken, const std::string deletingDate, const std::uint32_t generatedID) = 0;
    virtual void closeSession(int socketFD) = 0;
    virtual void addFile(size_t nodeID, std::string const & fileName) = 0;
    virtual std::vector<std::pair<std::string, std::string>> nodesQuery(unsigned int userID) = 0;
    virtual std::pair<std::multiset<Node>, std::set<std::uint32_t> > allNodes() = 0;
    virtual void deleteNode(std::uint32_t nodeID) = 0;
    virtual void deleteFilesFromNode(size_t nodeID) = 0;
    virtual void deleteFile(size_t nodeID, std::string const & fileName) = 0;
    virtual std::vector<std::string> getFilesList(std::uint32_t nodeID) = 0;
    virtual ~IDataBase() = default;

};


