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
    auto nodes = clientInterface->getNodes();

    for (auto & node : nodes)
    {
        auto files = clientInterface->getFiles(std::stoi(node.nodeID));
        node.fileNames = files;
        node.itemsIsLoaded = true;
        addNode(node);
    }

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

void NodesWindow::on_nodesTreeWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu(this);
    menu.addAction("Download");
    menu.addAction("Delete");
}
