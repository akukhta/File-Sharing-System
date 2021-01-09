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
    if (clientInterface->authorize(email, pass))
        accept();
    else
        ErrorMessage("Check inputed data.", "Register error");
}

void StartingWindow::on_logInButton_clicked()
{
    std::unique_ptr<AuthorizationWindow> window = std::make_unique<AuthorizationWindow>(clientInterface, false);
    if (!Configuration::showWindowAsFixed(window.get()))
        return;
    std::string email = window->getEmail();
    std::string pass = window->getPass();
    if (clientInterface->authorize(email,pass, false))
    {
        accept();
        std::unique_ptr<NodesWindow> nodesWindow = std::make_unique<NodesWindow>(clientInterface);
        Configuration::showWindowAsFixed(nodesWindow.get());
    }
    else
    {
        ErrorMessage("User with current login and password doesn't exist.\nCheck inputed data.", "Login error");
    }
}

void StartingWindow::ErrorMessage(QString const &text, QString const &title)
{
    QMessageBox box;
    box.setText(text);
    box.setWindowTitle(title);
    box.exec();
}
