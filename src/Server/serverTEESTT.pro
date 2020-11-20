TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        AccountManager.cpp \
        EMailManager.cpp \
        Server.cpp \
        databaseobject.cpp \
        main.cpp

HEADERS += \
    AccountManager.h \
    EMailManager.h \
    Server.h \
    databaseobject.h

unix:!macx: LIBS += -lsqlite3
