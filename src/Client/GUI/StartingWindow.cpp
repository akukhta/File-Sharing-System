#include "StartingWindow.h"
#include "ui_StartingWindow.h"

StartingWindow::StartingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartingWindow)
{
    ui->setupUi(this);
}

StartingWindow::~StartingWindow()
{
    delete ui;
}

void StartingWindow::on_signUpBtn_clicked()
{

}
