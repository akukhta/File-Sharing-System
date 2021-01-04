#pragma once
#include <vector>
#include <string>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <Common/Configuration.h>
class DataBaseObject
{
public:
    DataBaseObject(std::string const & dbpath = Configuration::getDefaultPathDB());
    bool insertQuery(std::string querystr);
    bool authorizationQuery(std::string & email, std::string & password, size_t& userID);
    bool createSessionQuery(std::uint32_t sessiongToken, int socketID, int userID);
    void closeSession(int socketFD);
    std::vector<std::string> nodesQuery(unsigned int userID);
    ~DataBaseObject();
private:
    //Connection pointer to sqlite3 database
    sql::Driver *driver;
    sql::Connection *conn;
    //Only for test
    int returnVal;
    sql::ResultSet* abstractSelectQuery(std::string const &query);
};
