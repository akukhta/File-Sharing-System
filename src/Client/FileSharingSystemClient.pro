QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Application.cpp \
    Client.cpp \
    ClientInterface.cpp \
    Common/Configuration.cpp \
    Common/GUINodeItem.cpp \
    Common/FileRepresentation.h \
    Common/FileRepresentation.cpp \
    GUI/NodeCreatingWindow.cpp \
    GUI/NodesWindow.cpp \
    GUI/authorizationwindow.cpp \
    GUI/startingwindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Application.h \
    Client.h \
    ClientInterface.h \
    Common/Configuration.h \
    Common/GUINodeItem.h \
    Common/Node.h \
    Common/RequestReader.h \
    Common/RequestWritter.h \
    GUI/NodeCreatingWindow.h \
    GUI/NodesWindow.h \
    GUI/authorizationwindow.h \
    GUI/startingwindow.h \
    Common/ServerResults.h \
    mainwindow.h

FORMS += \
    GUI/authorizationwindow.ui \
    GUI/nodecreatingwindow.ui \
    GUI/nodeswindow.ui \
    GUI/startingwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
