#include "NodeCreatingWindow.h"
#include "ui_nodecreatingwindow.h"

NodeCreatingWindow::NodeCreatingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NodeCreatingWindow)
{
    ui->setupUi(this);
    ui->lifeTimesBox->addItems(lifeTimes);
}

NodeCreatingWindow::~NodeCreatingWindow()
{
    delete ui;
}

void NodeCreatingWindow::on_selectDirectoryBtn_clicked()
{
    directoryPath = QFileDialog::getExistingDirectory(this, tr("Select a directory"));
    ui->pathEdit->setText(directoryPath);
    updateList();
}

void NodeCreatingWindow::updateList()
{
    ui->filesList->clear();

    auto fileNames = QDir(directoryPath).entryList();

#ifdef linux
    fileNames.removeOne(".");
    fileNames.removeOne("..");
#endif

    for (auto file : fileNames)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(file.right(file.length() - file.lastIndexOf("/") - 1));
        item->setCheckState(Qt::CheckState::Unchecked);
        ui->filesList->addItem(item);
    }
}

std::vector<QString> NodeCreatingWindow::getFileNames()
{
    return fileNames;
}

long long NodeCreatingWindow::getLifeTimeInMins()
{
    long long lifeTime;

    switch (ui->lifeTimesBox->currentIndex()) {
    case 0:
        lifeTime = 30;
        break;
    case 1:
        lifeTime = 60;
        break;
    case 2:
        lifeTime = 180;
        break;
    case 3:
        lifeTime = 360;
        break;
    case 4:
        lifeTime = 720;
        break;
    case 5:
        lifeTime = 1440;
        break;
    }

    return lifeTime;
}

void NodeCreatingWindow::on_filesList_itemClicked(QListWidgetItem *item)
{
    if (item->checkState() == Qt::Checked)
    {
        fileNames.push_back(directoryPath + item->text());
    }
    else
    {
        auto fileName = std::find(fileNames.begin(), fileNames.end(), directoryPath + item->text());
        if (fileName != fileNames.end())
            fileNames.erase(fileName);
    }
}

void NodeCreatingWindow::on_createBtn_clicked()
{
    accept();
}
