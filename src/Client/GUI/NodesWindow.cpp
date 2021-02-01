#include "NodesWindow.h"
#include "ui_nodeswindow.h"

NodesWindow::NodesWindow(std::shared_ptr<ClientInterface> const & clientInterface, QWidget *parent) :
    clientInterface(clientInterface) ,QDialog(parent),
    ui(new Ui::NodesWindow)
{
    ui->setupUi(this);
    ui->nodesTreeWidget->setColumnCount(2);
    ui->nodesTreeWidget->setHeaderLabels({"Node ID", "Life time"});
    auto nodes = clientInterface->getNodes();

    for (auto const & node : nodes)
    {
        addNode(node);
    }

}

void NodesWindow::addNode(Node const &node)
{
    guiItems.emplace_back(node);
    auto item = (--guiItems.end())->getGUIItem(ui->nodesTreeWidget).release();
    ui->nodesTreeWidget->addTopLevelItem(item);

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
    try{
        auto node = clientInterface->createNode(lifeTimeInMins);
        addNode(node);

    }
    catch (std::runtime_error const & err)
    {
        Configuration::showErrorDialog(err.what());
    }
}
