#ifndef DATABASEOBJECT_H
#define DATABASEOBJECT_H
#include <string>
#include <sqlite3.h>
#include <stdexcept>
#include <memory>
#include <Configuration.h>
class DataBaseObject
{
public:
    DataBaseObject(std::string const & dbpath = Configuration::getDefaultPathDB());
    bool query(std::string querystr);
    ~DataBaseObject();
private:
    //Connection pointer to sqlite3 database
    sqlite3 *db;
    //Only for test
    int returnVal;
};

#endif // DATABASEOBJECT_H
