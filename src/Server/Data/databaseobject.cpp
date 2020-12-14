#include "databaseobject.h"


DataBaseObject::DataBaseObject(std::string const &dbpath)
{
    try{
        driver = get_driver_instance();
        conn = driver->connect(Configuration::getDefaultPathDB(),
            Configuration::getDefaultUserDB(), Configuration::getDefaultPassDB());
        conn->setSchema("FileSharingSystem");
    }
    catch (sql::SQLException const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

//This method doesn't work, but i dont know why
bool DataBaseObject::insertQuery(std::string querystr)
{
    sql::Statement* statement = conn->createStatement();

    try{
        statement->execute(querystr);
    }
    catch (sql::SQLException const &ex)
    {
        std::cout << ex.what() << std::endl;
        delete statement;
        return false;
    }

    delete statement;
    return true;
}

DataBaseObject::~DataBaseObject()
{
    if (conn->isClosed())
        conn->close();
    delete conn;
}
