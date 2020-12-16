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
