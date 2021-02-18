#pragma once
#include <vector>
#include <set>
#include <string>
#include <mutex>
#include <mariadb/mysql.h>
#include "Data/IDataBase.h"
#include "Common/Configuration.h"
#include "Common/Node.h"
#include "Common/di.hpp"

auto serverName = []{};
auto userName = []{};
auto password = []{};
auto databaseName = []{};

class MySQLDatabase : public IDataBase
{
public:
    BOOST_DI_INJECT(MySQLDatabase, (named = serverName) std::string const & server,
        (named = userName) std::string const & user,
        (named = password) std::string const & password,
        (named = databaseName) std::string const & database);

    virtual bool insertQuery(std::string querystr) override final;
    virtual bool authorizationQuery(std::string const & email, std::string const & password, size_t &userID) override final;
    virtual bool createSessionQuery(std::uint32_t sessionToken, int socketID, int userID) override final;
    virtual Node createNode(const std::uint32_t sessionToken, const std::string deletingDate, const std::uint32_t generatedID) override final;
    virtual void closeSession(int socketFD) override final;
    virtual std::vector<std::pair<std::string, std::string>> nodesQuery(unsigned int userID) override final;
    virtual std::pair<std::multiset<Node>, std::set<std::uint32_t> > allNodes() override final;
    virtual void deleteNode(std::uint32_t nodeID) override final;
    virtual void addFile(size_t nodeID, std::string const & fileName) override final;
    virtual void deleteFilesFromNode(size_t nodeID) override final;
    virtual void deleteFile(size_t nodeID, std::string const & fileName) override final;
    virtual std::vector<std::string> getFilesList(std::uint32_t nodeID) override final;
    ~MySQLDatabase();
private:
    //Strings to configure mysql connection
    const std::string server = "localhost", user = "root",
        password = "root", database = "FileSharingSystem";
    //Only for test
    int returnVal;
    MYSQL* conn;
    MYSQL_RES* abstractSelectQuery(std::string const &query);
    std::mutex dataBaseMutex;
};
