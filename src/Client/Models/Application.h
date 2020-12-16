#pragma once
#include <QMessageBox>
#include <memory>
#include "BL/ClientInterface.h"
#include "GUI/startingwindow.h"

class Application
{
public:
    Application();
    void start();
private:
    std::shared_ptr<ClientInterface> clientInterface;
};

