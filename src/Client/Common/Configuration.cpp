#include "Configuration.h"

bool Configuration::showWindowAsFixed(QDialog* window)
{
    window->setFixedSize(window->size());
    return window->exec();
}

std::string Configuration::getServerIP()
{
    return "127.0.0.1";
}

int Configuration::getServerPort()
{
    return htons(5441);
}

void Configuration::showErrorDialog(std::string const &errorMessage)
{
    QMessageBox box;
    box.setWindowTitle("Error");
    box.setText(QString::fromStdString(errorMessage));
    box.exec();
}

std::string Configuration::getDeletingDate(long long lifeTimeInMins)
{
    auto deletingDate = std::chrono::system_clock::now() + std::chrono::minutes(lifeTimeInMins);
    auto t = std::chrono::system_clock::to_time_t(deletingDate);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

Configuration::OS Configuration::getOS()
{
#ifdef __linux__
    return OS::Linux;
#endif

#ifdef _win32
    return OS::Windows;
#endif
}
