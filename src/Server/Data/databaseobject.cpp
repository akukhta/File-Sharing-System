#include "databaseobject.h"


DataBaseObject::DataBaseObject(std::string const &dbpath)
{
    try{
        driver = get_driver_instance();
        conn = driver->connect(dbpath,
        Configuration::getDefaultUserDB(), Configuration::getDefaultPassDB());
        conn->setSchema("FileSharingSystem");
    }
    catch (sql::SQLException const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

//Simple INSERT/DELETE query, without any returned values.
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

//Basic select query

sql::ResultSet* DataBaseObject::abstractSelectQuery(std::string const &query)
{
    sql::Statement* statement = conn->createStatement();
    sql::ResultSet* result = nullptr;
    
    try{
        result = statement->executeQuery(query);
    }

    catch (sql::SQLException const &ex)
    {
        std::cout << ex.what() << std::endl;
        delete statement;
        return nullptr;
    }
    delete statement;
    return result;
}

//Authorization method
bool DataBaseObject::authorizationQuery(std::string const & email,
        std::string const & password, size_t &userID)
{
    std::lock_guard<std::mutex> lock(dataBaseMutex);

    const std::string query = "select * from Users where Email = \'"
            + email + "\' and Password = \'" + password + "\';";

    bool returnValue = false;

    sql::ResultSet *result = abstractSelectQuery(query);
    
    if (result != nullptr && result->rowsCount() == 1)
    {
        result->next();
        userID = result->getInt("UserID");
        returnValue = true;
    }
    
    delete result;
    
    return returnValue;
}

//Method for new sessiong creating
bool DataBaseObject::createSessionQuery(std::uint32_t sessionToken, int socketID, int userID)
{
    std::lock_guard<std::mutex> lock(dataBaseMutex);

    const std::string query = "insert into Sessions values (" + std::to_string(sessionToken)
            + "," + std::to_string(socketID) + "," + std::to_string(userID) + ");";
    return insertQuery(query);
}

std::pair<std::multiset<Node>, std::set<std::uint32_t>> DataBaseObject::allNodes()
{
    std::lock_guard<std::mutex> lock(dataBaseMutex);

    auto resultSet = abstractSelectQuery("select * from Nodes;");
    std::multiset<Node> nodes;
    std::set<std::uint32_t> ids;

    if (resultSet != nullptr)
    {
        while(resultSet->next())
        {
            int ID = resultSet->getInt("NodeID");
            nodes.emplace(ID, resultSet->getString("deletingDate").asStdString());
            ids.insert(ID);
        }
    }

    return std::make_pair(nodes, ids);
}


//Method for sessiong deleting
void DataBaseObject::closeSession(int socketFD)
{
    std::lock_guard<std::mutex> lock(dataBaseMutex);
    std::string query = "delete from Sessions where socketID = " + std::to_string(socketFD) + ";";
    insertQuery(query);
}

std::vector<std::pair<std::string, std::string>> DataBaseObject::nodesQuery(unsigned int sessionToken)
{
    std::lock_guard<std::mutex> lock(dataBaseMutex);

    const std::string query = "select * from Nodes where UserID = (select UserID from Sessions where sessionToken = " + std::to_string(sessionToken) + ");";
    sql::ResultSet *result = abstractSelectQuery(query);
    
    if (result == nullptr)
        throw std::runtime_error("Nodes query has been failed!");
    
    std::vector<std::pair<std::string, std::string>> nodes;

    while (result->next())
    {
        nodes.push_back(std::make_pair(std::to_string(result->getInt("NodeID")), result->getString("deletingDate")));
    }

    return nodes;
}

Node DataBaseObject::createNode(const std::uint32_t sessionToken, const std::string deletingDate, const std::uint32_t generatedID)
{

     std::lock_guard<std::mutex> lock(dataBaseMutex);

     const std::string query = "insert into Nodes(NodeID, UserID, deletingDate) values("
     + std::to_string(generatedID) + ", (select UserID from Sessions where sessionToken = "
     + std::to_string(sessionToken) + ")," + "\'" + deletingDate
     + "\');";

     if (!insertQuery(query))
     {
        throw std::runtime_error("Couldn`t create a new node!");
     }
     return Node(generatedID, deletingDate);
}

void DataBaseObject::deleteNode(std::uint32_t nodeID)
{
    std::lock_guard<std::mutex> lock(dataBaseMutex);
    const std::string query = "delete from Nodes where NodeID = " + std::to_string(nodeID) + ";";
    insertQuery(query);
}

DataBaseObject::~DataBaseObject()
{
    if (conn->isClosed())
        conn->close();
    delete conn;
}
