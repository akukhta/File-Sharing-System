#pragma once
#include <QDialog>
#include <memory>
#include <arpa/inet.h>

//Class which constains default settingns and used utilites
class Configuration final
{
public:
//Objects' creation and copying disabling
    Configuration() = delete;
    Configuration(Configuration const&) = delete;
    Configuration& operator=(Configuration const&) = delete;

//Shows the form as non-resizable
    static bool showWindowAsFixed(QDialog* window);
//Returns default server's address
    static std::string getServerIP();
//Returns default server's port
    static int getServerPort();
};

