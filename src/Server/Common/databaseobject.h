#ifndef DATABASEOBJECT_H
#define DATABASEOBJECT_H
#include <string>
#include <sqlite3.h>
#include <stdexcept>

class DataBaseObject
{
public:
    DataBaseObject(std::string const & dbpath = "/home/alex/build-serverTEESTT-Desktop-Debug/users.db");
    bool query(std::string querystr);
    ~DataBaseObject();
private:
    //Connection pointer to sqlite3 database
    sqlite3 *db;
    //Error message
    char *error = nullptr;
    //Only for test
    int returnVal;
};

#endif // DATABASEOBJECT_H
