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
BL/NodesManager.cpp)
target_link_libraries(FileSharingSystemServer mysqlcppconn)
file(COPY Resources/email.sh
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
