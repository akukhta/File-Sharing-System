#include "AuthorizationWindow.h"
#include "ui_AuthorizationWindow.h"

AuthorizationWIndow::AuthorizationWIndow(bool isSignUp,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthorizationWIndow)
{
    ui->setupUi(this);
    if (!isSignUp)
    {
        ui->repeatPassLbl->setVisible(0);
        ui->repeatPassEdit->setVisible(0);
        ui->authorizationBtn->setText("Log in");
    }
}

AuthorizationWIndow::~AuthorizationWIndow()
{
    delete ui;
}
