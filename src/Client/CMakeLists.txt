cmake_minimum_required(VERSION 3.5)

project(FSSClient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(FSSClient SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Application.h
    Application.cpp
    Client.h
    Client.cpp
    ClientInterface.h
    ClientInterface.cpp
    Common/Configuration.cpp
    Common/Configuration.h
    Common/FileRepresentation.h
    Common/FileRepresentation.cpp
    Common/GUINodeItem.h
    Common/GUINodeItem.cpp
    Common/Node.h
    Common/RequestReader.h
    Common/RequestWritter.h
    Common/ServerResults.h
    GUI/authorizationwindow.ui
    GUI/authorizationwindow.h
    GUI/authorizationwindow.cpp
    GUI/NodeCreatingWindow.ui
    GUI/NodeCreatingWindow.h
    GUI/NodeCreatingWindow.cpp
    GUI/NodesWindow.ui
    GUI/NodesWindow.h
    GUI/NodesWindow.cpp
    GUI/startingwindow.ui
    GUI/startingwindow.h
    GUI/startingwindow.cpp
  )
else()
  add_executable(FSSClient
      main.cpp
      mainwindow.cpp
      mainwindow.h
      mainwindow.ui
      Application.h
      Application.cpp
      Client.h
      Client.cpp
      ClientInterface.h
      ClientInterface.cpp
      Common/Configuration.cpp
      Common/Configuration.h
      Common/FileRepresentation.h
      Common/FileRepresentation.cpp
      Common/GUINodeItem.h
      Common/GUINodeItem.cpp
      Common/Node.h
      Common/RequestReader.h
      Common/RequestWritter.h
      Common/ServerResults.h
      GUI/authorizationwindow.ui
      GUI/authorizationwindow.h
      GUI/authorizationwindow.cpp
      GUI/nodecreatingwindow.ui
      GUI/NodeCreatingWindow.h
      GUI/NodeCreatingWindow.cpp
      GUI/nodeswindow.ui
      GUI/NodesWindow.h
      GUI/NodesWindow.cpp
      GUI/startingwindow.ui
      GUI/startingwindow.h
      GUI/startingwindow.cpp
  )
endif()

target_link_libraries(FSSClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
