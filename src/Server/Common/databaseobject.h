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
    sqlite3 *db;
    char *error;
    int returnVal;
};

#endif // DATABASEOBJECT_H
