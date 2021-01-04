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

    std::unique_ptr<StartingWindow> startingWindow = std::make_unique<StartingWindow>(clientInterface);
    Configuration::showWindowAsFixed(startingWindow.get());
    if (clientInterface->authorized())
    {
        std::unique_ptr<NodesWindow> nodesWindow = std::make_unique<NodesWindow>(clientInterface);
        Configuration::showWindowAsFixed(nodesWindow.get());
    }
}
