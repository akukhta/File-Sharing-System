cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(FileSharingSystemServer)
add_executable(FileSharingSystemServer main.cpp API/RequestHandler.cpp API/Server.cpp BL/AccountManager.cpp Common/databaseobject.cpp Common/EMailManager.cpp Common/Configuration.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lsqlite3-dev")
