cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(FileSharingSystemServer)

set (CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(FileSharingSystemServer 
    main.cpp
    API/RequestHandler.cpp
    API/Server.cpp
    BL/AccountManager.cpp
    BL/NodesManager.cpp
    BL/IAccountManager.h
    BL/INodesManager.h
    Data/databaseobject.cpp
    Data/EMailManager.cpp
    Data/AccountsRepository.cpp
    Data/DataBaseSingleton.cpp
    Data/AbstractAccountRepository.h
    Data/AbstractNodesRepository.h
    Data/NodesRepository.cpp
    Data/NodesRepository.h
    Common/Configuration.cpp
    Common/ServerResults.h
    Common/ClientException.h
    Common/Node.cpp
    Common/Node.h
    Common/di.hpp
    Common/Logger.cpp
    Common/Logger.h
)

target_link_libraries(FileSharingSystemServer mysqlcppconn pthread)
target_compile_options(FileSharingSystemServer PRIVATE -Werror -Wall -Wextra)

file(COPY Resources/email.sh
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
