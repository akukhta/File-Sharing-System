#include "NodesWindow.h"
#include "ui_nodeswindow.h"

NodesWindow::NodesWindow(std::shared_ptr<ClientInterface> const & clientInterface, QWidget *parent) :
    clientInterface(clientInterface) ,QDialog(parent),
    ui(new Ui::NodesWindow)
{
    ui->setupUi(this);
    ui->nodesTreeWidget->setColumnCount(2);
    ui->nodesTreeWidget->setHeaderLabels({"Node ID", "Life time"});
    ui->nodesTreeWidget->resizeColumnToContents(1);
    ui->nodesTreeWidget->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->nodesTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    fillTreeView();
}

void NodesWindow::addNode(Node const &node)
{
    guiItems.emplace_back(node);
    auto item = (--guiItems.end())->getGUIItem(ui->nodesTreeWidget).release();
    ui->nodesTreeWidget->addTopLevelItem(item);
    ui->nodesTreeWidget->resizeColumnToContents(1);
    ui->nodesTreeWidget->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
//    QTreeWidgetItem *item = new QTreeWidgetItem(ui->nodesTreeWidget);
//    item->setText(0, QString::fromStdString(nodeID));
//    item->addChild(new QTreeWidgetItem());
    //    ui->nodesTreeWidget->addTopLevelItem(item);
}

void NodesWindow::fillTreeView()
{
    ui->nodesTreeWidget->clear();

    auto nodes = clientInterface->getNodes();

    for (auto & node : nodes)
    {
        auto files = clientInterface->getFiles(std::stoi(node.nodeID));
        node.fileNames = files;
        node.itemsIsLoaded = true;
        addNode(node);
        selectedItemCounter[node.nodeID] = 0;
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
    bool folderIsSelected = false;
    std::string downloadingFolder;

    std::function<QTreeWidgetItem*(size_t)> nodes = [this](size_t index) {return ui->nodesTreeWidget->topLevelItem(index);};
    std::function<QTreeWidgetItem*(size_t, size_t)> files = [this](size_t nodesIndex, size_t filesIndex) {return ui->nodesTreeWidget->topLevelItem(nodesIndex)->child(filesIndex);};

    for (size_t nodesIndex = 0; nodesIndex < ui->nodesTreeWidget->topLevelItemCount(); nodesIndex++)
    {
        auto nodeItem = nodes(nodesIndex);
        if (nodeItem->checkState(0) == Qt::Unchecked)
            continue;
        else
        {
            for (size_t filesIndex = 0; filesIndex < nodeItem->childCount(); filesIndex++)
            {
                auto fileItem = files(nodesIndex, filesIndex);
                if (fileItem->checkState(0) == Qt::Unchecked)
                    continue;
                else
                {
                    if (!folderIsSelected)
                    {
                        downloadingFolder =  QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                            QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();
                        folderIsSelected = true;
                    }

                    clientInterface->receiveFile(fileItem->text(1).toStdString(), downloadingFolder, static_cast<std::uint32_t>(nodeItem->text(0).toUInt()));
                }
            }
        }
    }
}

void NodesWindow::on_updateBtn_clicked()
{
    fillTreeView();
}

void NodesWindow::on_pushButton_2_clicked()
{
#define TOP_LEVEL_ITEM(INDEX) ui->nodesTreeWidget->topLevelItem(INDEX)
#define FILE(NODES_INDEX, FILES_INDEX) ui->nodesTreeWidget->topLevelItem(NODES_INDEX)->child(FILES_INDEX)

    for (size_t i = 0; i < ui->nodesTreeWidget->topLevelItemCount(); i++)
    {
        auto wholeNode = TOP_LEVEL_ITEM(i);

        if (wholeNode->checkState(0) == Qt::Checked)
        {
            for (size_t j = 0; j < wholeNode->childCount(); j++)
            {
                auto file = FILE(i,j);

                if (file->checkState(0) == Qt::Checked)
                {
                    try{
                        clientInterface->deleteFile(static_cast<std::uint64_t>(wholeNode->text(0).toUInt()), file->text(1).toStdString());
                        wholeNode->removeChild(file);
                        j--;
                    }
                    catch (std::runtime_error const &err)
                    {
                        Configuration::showErrorDialog(err.what());
                    }
                }
            }
        }
    }
}
