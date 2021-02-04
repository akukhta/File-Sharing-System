#pragma once
#include <vector>
#include <set>
#include <string>
#include <mutex>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include "Data/IDataBase.h"
#include "Common/Configuration.h"
#include "Common/Node.h"

class MySQLDatabase : public IDataBase
{
public:
    MySQLDatabase(std::string const & dbpath = Configuration::getDefaultPathDB());
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
    //Connection pointer to mysql database
    sql::Driver *driver;
    sql::Connection *conn;
    //Only for test
    int returnVal;
    sql::ResultSet* abstractSelectQuery(std::string const &query);
    std::mutex dataBaseMutex;
};
