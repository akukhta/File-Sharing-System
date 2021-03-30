#include "MySQLDataBase.h"


MySQLDatabase::MySQLDatabase(std::string const & server, std::string const & user,
    std::string const & password, std::string const & database)
{
    std::cout << "DB" << std::endl;

    conn = mysql_init(nullptr);

    if (!mysql_real_connect(conn, server.c_str(), user.c_str(), password.c_str(),
        database.c_str(),0, nullptr, 0))
    {
        throw std::runtime_error("Connection to the database failed");
    }

}

//Simple INSERT/DELETE query, without any returned values.
bool MySQLDatabase::insertQuery(std::string querystr)
{   
        std::lock_guard<std::mutex> lock(dataBaseMutex);
        return !mysql_query(conn, querystr.c_str());
}

//Basic select query

MYSQL_RES* MySQLDatabase::abstractSelectQuery(std::string const &query)
{
    std::lock_guard<std::mutex> lock(dataBaseMutex);
    if (mysql_query(conn, query.c_str()))
        return nullptr;
    else
        return mysql_store_result(conn);
}

//Authorization method
bool MySQLDatabase::authorizationQuery(std::string const & email,
        std::string const & password, size_t &userID)
{
    const std::string query = "select * from Users where Email = \'"
            + email + "\' and Password = \'" + password + "\';";

    bool returnValue = false;

    auto result = abstractSelectQuery(query);

    if (result && mysql_num_rows(result) == 1)
    {
        auto row = mysql_fetch_row(result);
        userID = std::stoi(row[0]);
        returnValue = true;
        mysql_free_result(result);
    }
    
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
    MYSQL_ROW row;

    if (resultSet != nullptr)
    {
        while((row = mysql_fetch_row(resultSet)) != nullptr)
        {
            int ID = std::stoi(row[0]);
            nodes.emplace(ID, std::string(row[2]));
            ids.insert(ID);
        }

        mysql_free_result(resultSet);
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
    auto result = abstractSelectQuery(query);

    if (result == nullptr)
        throw std::runtime_error("Nodes query has been failed!");
    
    std::vector<std::pair<std::string, std::string>> nodes;

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)) != nullptr)
    {
        nodes.push_back(std::make_pair(std::string(row[0]), std::string(row[2])));
    }

    mysql_free_result(result);
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
    auto nodeIDStr = std::to_string(nodeID);
    const std::string query = "delete from Nodes where NodeID = " + nodeIDStr + ";";
    std::cout << std::to_string(nodeID) << (insertQuery(query) == true ? " has been deleted from DB!"
                                            :   " hasn`t been deleted") << std::endl;;
    const std::string deleteFilesQuery = "delete from Files where NodeID = " + nodeIDStr + ";";
    insertQuery(deleteFilesQuery);
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

    insertQuery(query);
}

std::vector<std::string> MySQLDatabase::getFilesList(std::uint32_t nodeID)
{
    std::string const query = "select FileName from Files where NodeID = " + std::to_string(nodeID) + ";";

    auto result = abstractSelectQuery(query);

    if (result == nullptr)
        return std::vector<std::string>();

    std::vector<std::string> fileNames;

    MYSQL_ROW row;

    while((row = mysql_fetch_row(result)) != nullptr)
    {
        fileNames.push_back(std::string(row[0]));
    }

    mysql_free_result(result);
    return fileNames;
}

MySQLDatabase::~MySQLDatabase()
{
    mysql_close(conn);
    std::cout << "Data base has been deleted!" << std::endl;
}

