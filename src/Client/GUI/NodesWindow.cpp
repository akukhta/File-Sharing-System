#include "NodesWindow.h"
#include "ui_nodeswindow.h"

NodesWindow::NodesWindow(std::shared_ptr<ClientInterface> const & clientInterface, QWidget *parent) :
    clientInterface(clientInterface) ,QDialog(parent),
    ui(new Ui::NodesWindow)
{
    ui->setupUi(this);

    ui->nodesTreeWidget->setColumnCount(4);
    ui->nodesTreeWidget->setHeaderLabels({"","","Name", "Life time"});
    ui->nodesTreeWidget->header()->resizeSection(0, 20);
    ui->nodesTreeWidget->header()->resizeSection(1, 20);
    ui->nodesTreeWidget->header()->resizeSection(2, 400);
    ui->nodesTreeWidget->header()->resizeSection(3, 100);
    ui->nodesTreeWidget->setIconSize(QSize(30,30));
    ui->pushButton_2->setVisible(0);
    loadNodes();
}

void NodesWindow::addNode(Node const &node)
{
    GUINodeItem GUIItem(ui->nodesTreeWidget, node.nodeID,
                            node.deletingDate, GUINodeItem::GUINodeItemType::Node);

    guiNodes.insert(std::make_pair(GUIItem.getGUIItem(), node));

    ui->nodesTreeWidget->addTopLevelItem(GUIItem.getGUIItem());
}

void NodesWindow::loadNodes()
{
    ui->nodesTreeWidget->clear();

    auto nodes = clientInterface->getNodes();

    for (auto & node : nodes)
    {
        addNode(node);
    }
}

void NodesWindow::loadFilesInNode(std::string const nodeID, std::string const deletingDate)
{
    auto files = clientInterface->getFiles(std::stoi(nodeID));

    ui->nodesTreeWidget->clear();

    ui->nodesTreeWidget->addTopLevelItem(GUINodeItem(ui->nodesTreeWidget, "..", "", GUINodeItem::GUINodeItemType::UpCom).getGUIItem());

    for (auto file : files)
        ui->nodesTreeWidget->addTopLevelItem(GUINodeItem(ui->nodesTreeWidget, file, deletingDate, GUINodeItem::GUINodeItemType::File).getGUIItem());
}

std::vector<std::string> NodesWindow::getSelectedItems()
{
    std::vector<std::string> selectedNodes;

    for (size_t i = 0; i < ui->nodesTreeWidget->topLevelItemCount(); i++)
    {
        if (ui->nodesTreeWidget->topLevelItem(i)->checkState(0))
            selectedNodes.push_back(ui->nodesTreeWidget->topLevelItem(i)->text(2).toStdString());
    }

    return selectedNodes;
}

void NodesWindow::clearSelectection()
{
    for (size_t i = 0; i < ui->nodesTreeWidget->topLevelItemCount(); i++)
    {
        ui->nodesTreeWidget->topLevelItem(i)->setCheckState(0, Qt::CheckState::Unchecked);
    }
}

NodesWindow::~NodesWindow()
{
    delete ui;
}

void NodesWindow::on_createNodeBtn_clicked()
{
    if (!clientInterface->authorized())
        return;

    std::unique_ptr<NodeCreatingWindow> createWindow = std::make_unique<NodeCreatingWindow>();
    if (!Configuration::showWindowAsFixed(createWindow.get()))
        return;

    long long lifeTimeInMins = createWindow->getLifeTimeInMins();
    auto files = createWindow->getFileNames();

    try{

        auto node = clientInterface->createNode(lifeTimeInMins);
        std::vector<std::string> filesStr;

        std::for_each(files.begin(), files.end(), [&filesStr](QString const & x)
        {
            auto name = x.toStdString();
            name = name.substr(name.find_last_of(std::filesystem::path::preferred_separator) + 1);
            filesStr.push_back(name);}
        );

        node.fileNames = filesStr;
        node.itemsIsLoaded = true;

        if (!currFocusInDir)
            addNode(node);

        selectedItemCounter[node.nodeID] = 0;
        auto nodeID = static_cast<std::uint32_t>(std::stoi(node.nodeID));
        for (auto & x : files)
        {
            try
            {
                clientInterface->sendFile(x.toStdString(), nodeID);
            } catch (std::runtime_error const & err)
            {
                Configuration::showErrorDialog(err.what());
            }
        }
    }
    catch (std::runtime_error const & err)
    {
        Configuration::showErrorDialog(err.what());
    }
}

void NodesWindow::on_nodesTreeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    //If we have changes not in check box column, we have to return from the function
    if (column != 0)
        return;

    if (!item->parent())
    {
        if (calledFromChild)
            return;

        auto  checkState = item->checkState(0) ? Qt::Checked : Qt::Unchecked;

        for (size_t i = 0; i < item->childCount(); i++)
            item->child(i)->setCheckState(0, checkState);

        if (checkState == Qt::Checked)
        {
            selectedItemCounter[item->text(0).toStdString()] = item->childCount();
        }
        else
        {
            selectedItemCounter[item->text(0).toStdString()] = 0;
        }
    }
    else
    {
        int modifier = item->checkState(0) == Qt::Checked ? 1 : -1;
        selectedItemCounter[item->parent()->text(0).toStdString()] += modifier;
        auto state = selectedItemCounter.at(item->parent()->text(0).toStdString()) > 0 ? Qt::Checked : Qt::Unchecked;

        if (item->parent() != nullptr)
        {
            calledFromChild = true;
            item->parent()->setCheckState(0, state);
            calledFromChild = false;
        }
    }
}

void NodesWindow::on_pushButton_clicked()
{
    std::string destFolder = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
        QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();

    if (!currFocusInDir)
    {
        auto selectedNodes = getSelectedItems();

        for (std::string node : selectedNodes)
        {
            std::uint32_t currNodeInt = static_cast<std::uint32_t>(std::stoi(node));
            auto files = clientInterface->getFiles(currNodeInt);

            for (auto file : files)
            {
                clientInterface->receiveFile(file, destFolder, currNodeInt);
            }
        }
    }

    else
    {
        auto selectedFiles = getSelectedItems();

        for (auto file : selectedFiles)
        {
            clientInterface->receiveFile(file, destFolder, static_cast<std::uint32_t>(std::stoi(currentNode)));
        }
    }

    clearSelectection();

}

void NodesWindow::on_updateBtn_clicked()
{
    if (!currFocusInDir)
    {
        loadNodes();
    }
    else
    {
        loadFilesInNode(currentNode, currentNodeDeletingDate);
    }
}

void NodesWindow::on_pushButton_2_clicked()
{
    if (!currFocusInDir)
        return;

    for (size_t i = 0; i < ui->nodesTreeWidget->topLevelItemCount(); i++)
    {
        if (ui->nodesTreeWidget->topLevelItem(i)->checkState(0) == Qt::CheckState::Checked)
        {
            try
            {
            clientInterface->deleteFile(static_cast<std::uint32_t>(std::stoi(currentNode)),
                ui->nodesTreeWidget->topLevelItem(i)->text(2).toStdString());
            loadFilesInNode(currentNode, currentNodeDeletingDate);
            }
            catch (std::runtime_error const &err)
            {
                Configuration::showErrorDialog(err.what());
            }
        }
    }

}

void NodesWindow::on_nodesTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{

    if (column == 0)
        return;

    if (!currFocusInDir)
    {
        currFocusInDir = true;
        auto selectedNode = guiNodes.at(item);
        currentNode = selectedNode.nodeID;
        currentNodeDeletingDate = selectedNode.deletingDate;
        loadFilesInNode(selectedNode.nodeID, selectedNode.deletingDate);
        ui->createNodeBtn->setVisible(0);
        ui->pushButton_2->setVisible(1);
    }

    else if (item->text(2) == "..")
    {
        loadNodes();
        currFocusInDir = false;
        ui->createNodeBtn->setVisible(1);
        ui->pushButton_2->setVisible(0);
    }

    ui->nodesTreeWidget->repaint();
    ui->nodesTreeWidget->update();
    ui->nodesTreeWidget->model()->dataChanged(ui->nodesTreeWidget->model()->index(0,0), ui->nodesTreeWidget->model()->index(ui->nodesTreeWidget->model()->rowCount(),0));
}
