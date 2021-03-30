#include "nodedownloadingwindow.h"
#include "ui_nodedownloadingwindow.h"

NodeDownloadingWindow::NodeDownloadingWindow(std::shared_ptr<ClientInterface> &clientInterface, QWidget *parent) :
    clientInterface(clientInterface), QWidget(parent),
    ui(new Ui::NodeDownloadingWindow)
{
    ui->setupUi(this);
}

NodeDownloadingWindow::~NodeDownloadingWindow()
{
    delete ui;
}
