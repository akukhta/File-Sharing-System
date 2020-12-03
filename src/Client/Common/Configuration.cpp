#include "Configuration.h"

void Configuration::showWindowAsFixed(QWidget& window)
{
    window.setFixedSize(window.size());
    window.show();
}

std::string Configuration::getServerIP()
{
    return "127.0.0.1";
}

int Configuration::getServerPort()
{
    return 5441;
}
