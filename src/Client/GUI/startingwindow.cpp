#include "startingwindow.h"
#include "ui_startingwindow.h"

StartingWindow::StartingWindow(std::shared_ptr<ClientInterface> &clientInterface,QWidget *parent) :
    clientInterface(clientInterface), QDialog(parent),
    ui(new Ui::StartingWindow)
{
    ui->setupUi(this);

}

StartingWindow::~StartingWindow()
{
    delete ui;
}

void StartingWindow::on_pushButton_clicked()
{
    ;
}

void StartingWindow::on_pushButton_2_clicked()
{
    ;
}

void StartingWindow::on_signInButton_clicked()
{
    std::unique_ptr<AuthorizationWindow> window = std::make_unique<AuthorizationWindow>(clientInterface);
    if (!Configuration::showWindowAsFixed(window.get()))
        return;
    std::string email = window->getEmail();
    std::string pass = window->getPass();
    clientInterface->authorize(email, pass);
}

void StartingWindow::on_logInButton_clicked()
{
    std::unique_ptr<AuthorizationWindow> window = std::make_unique<AuthorizationWindow>(clientInterface, false);
    if (!Configuration::showWindowAsFixed(window.get()))
        return;
    std::string email = window->getEmail();
    std::string pass = window->getPass();
    clientInterface->authorize(email,pass, false);
}
