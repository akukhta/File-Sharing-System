cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(FileSharingSystemServer)

include_directories(.)

add_executable(FileSharingSystemServer 
    main.cpp
    API/RequestHandler.cpp
    API/Server.cpp
    BL/AccountManager.cpp
    Data/databaseobject.cpp
    Data/EMailManager.cpp
    Common/Configuration.cpp
    Common/ServerResults.h
    Common/ClientException.h
    BL/NodesManager.cpp
    Common/Node.cpp
    Common/Node.h
    Data/AccountsRepository.cpp
    Data/DataBaseSingleton.cpp
    Common/di.hpp
    Common/AbstractAccountRepository.h
    Common/AbstractNodesRepository.h
    Data/NodesRepository.cpp
    Data/NodesRepository.h
)

target_link_libraries(FileSharingSystemServer mysqlcppconn pthread)
set (CMAKE_CXX_STANDARD 17)
file(COPY Resources/email.sh
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
