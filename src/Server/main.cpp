#include <iostream>
#include "Data/AccountsRepository.h"
#include "Data/NodesRepository.h"
#include "BL/IAccountManager.h"
#include "Common/di.hpp"
#include "API/Server.h"
#include "Data/IDataBase.h"
#include "Data/MySQLDataBase.h"
#include "Data/FilesRepository.h"

using namespace std;

int main()
{

    namespace di = boost::di;

    auto Injector = di::make_injector(
                di::bind<IDataBase>().in(di::singleton).to<MySQLDatabase>(),
                di::bind<std::string>.named(serverName).to(Configuration::getDefaultDBServer()),
                di::bind<std::string>.named(userName).to(Configuration::getDefaultDBUser()),
                di::bind<std::string>.named(password).to(Configuration::getDefaultDBPassword()),
                di::bind<std::string>.named(databaseName).to(Configuration::getDefaultDB()),
                di::bind<AbstractAccountRepository>().in(di::unique).to<AccountsRepository>(),
                di::bind<AbstractFilesRepository>().in(di::unique).to<FilesRepository>(),
                di::bind<AbstractNodesRepository>().in(di::unique).to<NodesRepository>(),
                di::bind<IAccountManager>().in(di::unique).to<AccountManager>(),
                di::bind<INodesManager>().in(di::unique).to<NodesManager>(),
                di::bind<IFilesManager>().in(di::singleton).to<FilesManager>(),
                di::bind<IRequestHandler>().in(di::unique).to<RequestHandler>(),
                di::bind<int>.to(5441),
                di::bind<size_t>.to(static_cast<size_t>(32)),
                di::bind<std::string>.to(std::string(Configuration::getDefaultIP()))
                );

    try
    {
        Injector.create<std::unique_ptr<Server>>()->run();
    }
    catch (std::runtime_error const & err)
    {
        Logger::log()->fatalError(err.what());
    }

    return 0;
}
