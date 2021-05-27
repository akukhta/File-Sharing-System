#pragma once
#include <QDialog>
#include <QMessageBox>
#include <memory>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <arpa/inet.h>
#include <string>

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

    static void showErrorDialog(std::string const &errorMessage);

    static std::string getDeletingDate(long long lifeTimeInMins);

    enum class OS {Linux, Windows};

    static OS getOS();
};

