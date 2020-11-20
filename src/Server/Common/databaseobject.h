#ifndef DATABASEOBJECT_H
#define DATABASEOBJECT_H
#include <string>
#include <sqlite3.h>
#include <stdexcept>

class DataBaseObject
{
public:
    DataBaseObject(std::string const & dbpath = "users");
    bool query(std::string querystr);
    ~DataBaseObject();
private:
    sqlite3 *db;
};

#endif // DATABASEOBJECT_H
