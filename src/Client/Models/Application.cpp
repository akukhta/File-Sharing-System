#include "Application.h"

Application::Application() : clientInterface(std::make_shared<ClientInterface>(std::make_unique<Client>()))
{
    ;
}

void Application::start()
{
    if (clientInterface->connectToServer() == false)
    {
        QMessageBox box;
        box.setText("Can't connect to server!");
        box.setWindowTitle("Connection error");
        box.exec();
        return;
    }

    std::unique_ptr<StartingWindow> window = std::make_unique<StartingWindow>(clientInterface);
    Configuration::showWindowAsFixed(window.get());
}
