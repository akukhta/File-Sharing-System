#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"

AuthorizationWindow::AuthorizationWindow(std::shared_ptr<ClientInterface>& clientInterface, bool isSigup, QWidget *parent) :
    clientInterface(clientInterface), QDialog(parent),
    ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
    if (!isSigup)
    {
        ui->passConf_edit->setVisible(0);
        ui->passConLbl->setVisible(0);
        ui->logBtn->setText("Log in");
    }
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

void AuthorizationWindow::on_logBtn_clicked()
{
    accept();
}

std::string AuthorizationWindow::getEmail()
{
    return ui->email_edit->text().toStdString();
}

std::string AuthorizationWindow::getPass()
{
    return ui->pass_edit->text().toStdString();
}
