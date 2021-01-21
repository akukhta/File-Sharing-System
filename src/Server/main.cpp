#include <iostream>
#include "Common/di.hpp"
#include "API/Server.h"
#include "Data/AccountsRepository.h"
#include <Data/NodesRepository.h>

using namespace std;

int main()
{

    //This code doesn`t work, but if i replace all smart pointers to references, it'll be ok
    auto injector = boost::di::make_injector(
                boost::di::bind<AbstractAccountRepository>.to<AccountsRepository>(),
                boost::di::bind<AbstractNodesRepository>.to<NodesRepository>());
    injector.create<Server>().run();
    return 0;
}
