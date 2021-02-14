cmake_minimum_required(VERSION 3.5)

project(FileSharingSystemServer)

set (CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(FileSharingSystemServer 
    main.cpp
    API/IRequestHandler.h
    API/RequestHandler.cpp
    API/Server.cpp
    BL/AccountManager.cpp
    BL/NodesManager.cpp
    BL/IAccountManager.h
    BL/INodesManager.h
    BL/IFilesManager.h
    BL/FilesManager.h
    BL/FilesManager.cpp
    Data/MySQLDataBase.cpp
    Data/EMailManager.cpp
    Data/AccountsRepository.cpp
    Data/DataBaseSingleton.cpp
    Data/AbstractAccountRepository.h
    Data/AbstractNodesRepository.h
    Data/NodesRepository.cpp
    Data/NodesRepository.h
    Data/IDataBase.h
    Data/FileRepresentation.cpp
    Data/FileRepresentation.h
    Data/AbstractFilesRepository.h
    Data/FilesRepository.h
    Data/FilesRepository.cpp
    Common/Configuration.cpp
    Common/ServerResults.h
    Common/ClientException.h
    Common/Node.cpp
    Common/Node.h
    Common/di.hpp
    Common/Logger.cpp
    Common/Logger.h
)

target_link_libraries(FileSharingSystemServer pthread mariadbclient)
#target_compile_options(FileSharingSystemServer PRIVATE -Werror -Wall -Wextra)

file(COPY Resources/email.sh
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
