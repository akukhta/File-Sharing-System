#pragma once
#include <vector>
#include <set>
#include <string>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <Common/Configuration.h>
#include "Common/Node.h"

class DataBaseSingleton
{

protected:

    DataBaseSingleton(std::string const & dbpath = Configuration::getDefaultPathDB());
    static std::shared_ptr<DataBaseSingleton> dataBase;

public:

    DataBaseSingleton(DataBaseSingleton const &) = delete;
    void operator=(DataBaseSingleton const &) = delete;

    static std::shared_ptr<DataBaseSingleton> getInstance(std::string const & dbpath = Configuration::getDefaultPathDB());
    bool insertQuery(std::string querystr);
    bool authorizationQuery(std::string const & email, std::string const & password, size_t &userID);
    bool createSessionQuery(std::uint32_t sessionToken, int socketID, int userID);
    bool createNode(const std::uint32_t sessionToken, const std::string deletingDate, const std::uint32_t generatedID);
    void closeSession(int socketFD);
    std::vector<std::pair<std::string, std::string>> nodesQuery(unsigned int userID);
    std::pair<std::set<Node>, std::set<std::uint32_t> > allNodes();
    ~DataBaseSingleton();

private:

    //Connection pointer to mysql database
    sql::Driver *driver;
    sql::Connection *conn;
    //Only for test
    int returnVal;
    sql::ResultSet* abstractSelectQuery(std::string const &query);
};

std::shared_ptr<DataBaseSingleton> DataBaseSingleton::dataBase = nullptr;
