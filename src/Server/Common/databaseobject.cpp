#include "databaseobject.h"

DataBaseObject::DataBaseObject(std::string const &dbpath)
{
    if (sqlite3_open(dbpath.c_str(), &this->db))
        throw std::runtime_error("Database didn't open!");

}

bool DataBaseObject::query(std::string querystr)
{
    char *error;
    return sqlite3_exec(this->db, querystr.c_str(), nullptr,nullptr, &error);
}

DataBaseObject::~DataBaseObject()
{
    sqlite3_close(this->db);
}
