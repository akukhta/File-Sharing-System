#include "databaseobject.h"


DataBaseObject::DataBaseObject(std::string const &dbpath)
{
    if (sqlite3_open(dbpath.c_str(), &db) != SQLITE_OK)
        throw std::runtime_error("Database didn't open!");

}

//This method doesn't work, but i dont know why
bool DataBaseObject::query(std::string querystr)
{
    if (this->db == nullptr)
    returnVal =  sqlite3_exec(this->db, querystr.c_str(), nullptr,nullptr, nullptr);
    return returnVal;
}

DataBaseObject::~DataBaseObject()
{
    sqlite3_close(this->db);
}
