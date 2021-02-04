#include "MySQLDataBase.h"


MySQLDatabase::MySQLDatabase(std::string const &dbpath)
{
    std::cout << "DB" << std::endl;
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
bool MySQLDatabase::insertQuery(std::string querystr)
{   
    sql::Statement* statement = conn->createStatement();

    try{
        std::lock_guard<std::mutex> lock(dataBaseMutex);
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

sql::ResultSet* MySQLDatabase::abstractSelectQuery(std::string const &query)
{
    sql::Statement* statement = conn->createStatement();
    sql::ResultSet* result = nullptr;
    
    try{
        std::lock_guard<std::mutex> lock(dataBaseMutex);
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
bool MySQLDatabase::authorizationQuery(std::string const & email,
        std::string const & password, size_t &userID)
{
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
bool MySQLDatabase::createSessionQuery(std::uint32_t sessionToken, int socketID, int userID)
{
    const std::string query = "insert into Sessions values (" + std::to_string(sessionToken)
            + "," + std::to_string(socketID) + "," + std::to_string(userID) + ");";

    auto result = insertQuery(query);
    return result;
}

std::pair<std::multiset<Node>, std::set<std::uint32_t>> MySQLDatabase::allNodes()
{
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
void MySQLDatabase::closeSession(int socketFD)
{
    std::string query = "delete from Sessions where socketID = " + std::to_string(socketFD) + ";";
    insertQuery(query);
}

std::vector<std::pair<std::string, std::string>> MySQLDatabase::nodesQuery(unsigned int sessionToken)
{
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

Node MySQLDatabase::createNode(const std::uint32_t sessionToken, const std::string deletingDate, const std::uint32_t generatedID)
{
     const std::string query = "insert into Nodes(NodeID, UserID, deletingDate) values("
     + std::to_string(generatedID) + ", (select UserID from Sessions where sessionToken = "
     + std::to_string(sessionToken) + ")," + "\'" + deletingDate
     + "\');";

     if (!insertQuery(query))
     {
        throw std::runtime_error("Couldn`t create a new node!");
     }

     std::cout << std::to_string(generatedID) << " has been created" << std::endl;
     return Node(generatedID, deletingDate);
}

void MySQLDatabase::deleteNode(std::uint32_t nodeID)
{
    const std::string query = "delete from Nodes where NodeID = " + std::to_string(nodeID) + ";";
    std::cout << std::to_string(nodeID) << (insertQuery(query) == true ? " has been deleted from DB!"
                                            :   " hasn`t been deleted") << std::endl;;
}

void MySQLDatabase::addFile(size_t nodeID, std::string const & fileName)
{
    std::string const query = "insert into Files(NodeID, FileName) values ("
            + std::to_string(nodeID) + ", \'" + fileName + "\');";

    if(!insertQuery(query))
    {
        throw std::runtime_error("Failed to insert file into the Data Base");
    }

}

void MySQLDatabase::deleteFilesFromNode(size_t nodeID)
{
    std::string const query = "delete from Files where NodeID = " + std::to_string(nodeID) + ";";

    if (!insertQuery(query))
    {
        throw std::runtime_error("Failed to delete files from a node");
    }
}

void MySQLDatabase::deleteFile(size_t nodeID, std::string const & fileName)
{
    std::string const query = "delete from Files where NodeID = " + std::to_string(nodeID)
            + " and FileName = \'" + fileName + "\';";

    if (!insertQuery(query))
    {
        throw std::runtime_error("Failed to delete a file from the Data Base");
    }
}

std::vector<std::string> MySQLDatabase::getFilesList(std::uint32_t nodeID)
{
    std::string const query = "select FileName from Files where NodeID = " + std::to_string(nodeID) + ";";

    auto result = abstractSelectQuery(query);

    if (result == nullptr)
        return std::vector<std::string>();

    std::vector<std::string> fileNames;

    while(result->next())
    {
        fileNames.push_back(result->getString("FileName"));
    }

    return fileNames;
}

MySQLDatabase::~MySQLDatabase()
{
    if (conn->isClosed())
        conn->close();
    std::cout << "Data base has been deleted!" << std::endl;
    delete conn;
}

