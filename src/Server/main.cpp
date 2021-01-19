#include <iostream>
#include "Common/di.hpp"
#include "API/Server.h"
#include "Data/AccountsRepository.h"

using namespace std;

int main()
{
    std::shared_ptr<DataBaseObject> db = std::make_shared<DataBaseObject>();
    std::unique_ptr<AbstractAccountRepository> accRep = std::make_unique<AccountsRepository>(db);
    std::unique_ptr<AccountManager> accountManager = std::make_unique<AccountManager>(accRep);
    std::unique_ptr<NodesManager> nodesManager = std::make_unique<NodesManager>(db);
    std::unique_ptr<RequestHandler> handler = std::make_unique<RequestHandler>(accountManager, nodesManager);
    std::unique_ptr<Server> server = std::make_unique<Server>(handler);

    try{
        server->run();
    }
     catch (std::runtime_error const & err)
    {
        std::cout << err.what() << std::endl;
    }
//    This code doesn`t work, but if i replace all smart pointers to references, it'll be ok
//    auto injector = boost::di::make_injector();
//    injector.create<Server>().run();
    return 0;
}
