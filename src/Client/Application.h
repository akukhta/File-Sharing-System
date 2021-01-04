#pragma once
#include <QMessageBox>
#include <memory>
#include "ClientInterface.h"
#include "GUI/startingwindow.h"
#include "GUI/NodesWindow.h"

class Application
{
public:
    Application();
    void start();
private:
    std::shared_ptr<ClientInterface> clientInterface;
};

