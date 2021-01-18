#include "DataBaseSingleton.h"

DataBaseSingleton::DataBaseSingleton(std::string const & dbpath)
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

std::shared_ptr<DataBaseSingleton> DataBaseSingleton::getInstance(std::string const & dbpath)
{
    if (!dataBase)
        dataBase = std::shared_ptr<DataBaseSingleton>(new DataBaseSingleton(dbpath));

    return dataBase;
}

//Simple INSERT/DELETE query, without any returned values.
bool DataBaseSingleton::insertQuery(std::string querystr)
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
sql::ResultSet* DataBaseSingleton::abstractSelectQuery(std::string const &query)
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
bool DataBaseSingleton::authorizationQuery(std::string const & email,
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
bool DataBaseSingleton::createSessionQuery(std::uint32_t sessionToken, int socketID, int userID)
{
    const std::string query = "insert into Sessions values (" + std::to_string(sessionToken)
            + "," + std::to_string(socketID) + "," + std::to_string(userID) + ");";
    return insertQuery(query);
}

std::pair<std::set<Node>, std::set<std::uint32_t>> DataBaseSingleton::allNodes()
{
    auto resultSet = abstractSelectQuery("select * from Nodes;");
    std::set<Node> nodes;
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
void DataBaseSingleton::closeSession(int socketFD)
{
    std::string query = "delete from Sessions where socketID = " + std::to_string(socketFD) + ";";
    insertQuery(query);
}

std::vector<std::pair<std::string, std::string>> DataBaseSingleton::nodesQuery(unsigned int sessionToken)
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

bool DataBaseSingleton::createNode(const std::uint32_t sessionToken, const std::string deletingDate, const std::uint32_t generatedID)
{
    const std::string query = "insert into Nodes(NodeID, UserID, deletingDate) values("
     + std::to_string(generatedID) + ", (select UserID from Sessions where sessionToken = "
     + std::to_string(sessionToken) + ")," + "\'" + deletingDate
     + "\');";
     return insertQuery(query);
}

DataBaseSingleton::~DataBaseSingleton()
{
    if (conn->isClosed())
        conn->close();
    delete conn;
}


