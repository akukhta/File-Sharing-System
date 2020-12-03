#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QWidget>

//Class which constains default settingns and used utilites
class Configuration final
{
public:
//Objects' creation and copying disabling
    Configuration() = delete;
    Configuration(Configuration const&) = delete;
    Configuration& operator=(Configuration const&) = delete;

//Shows the form as non-resizable
    static void showWindowAsFixed(QWidget& window);
//Returns default server's address
    static std::string getServerIP();
//Returns default server's port
    static int getServerPort();
};

#endif // CONFIGURATION_H
