#include "NodesWindow.h"
#include "ui_nodeswindow.h"

NodesWindow::NodesWindow(std::shared_ptr<ClientInterface> const & clientInterface, QWidget *parent) :
    clientInterface(clientInterface) ,QDialog(parent),
    ui(new Ui::NodesWindow)
{
    ui->setupUi(this);
    ui->nodesTreeWidget->setColumnCount(2);
    ui->nodesTreeWidget->setHeaderLabels({"Node ID", "Life time"});
    nodes = clientInterface->getNodes();

    for (auto node : nodes)
        addNode(node.nodeID);

}

void NodesWindow::addNode(std::string nodeID)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->nodesTreeWidget);
    item->setText(0, QString::fromStdString(nodeID));
    item->addChild(new QTreeWidgetItem());
    ui->nodesTreeWidget->addTopLevelItem(item);
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
        nodes.push_back(node);
        addNode(node.nodeID);
    }
    catch (std::runtime_error const & err)
    {
        Configuration::showErrorDialog(err.what());
    }
}
