#pragma once

#include <QDialog>
#include <QMenu>
#include <memory>
#include <vector>
#include <unordered_map>
#include <map>
#include "ClientInterface.h"
#include "Common/Node.h"
#include "GUI/NodeCreatingWindow.h"
#include "Common/GUINodeItem.h"

namespace Ui {
class NodesWindow;
}

class NodesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NodesWindow(std::shared_ptr<ClientInterface> const & clientInterface, QWidget *parent = nullptr);
    ~NodesWindow();

private slots:
    void on_createNodeBtn_clicked();

    void on_nodesTreeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_pushButton_clicked();

    void on_updateBtn_clicked();

    void on_pushButton_2_clicked();

    void on_nodesTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::NodesWindow *ui;
    void addNode(Node const &node);
    std::shared_ptr<ClientInterface> clientInterface;
    std::unordered_map<QTreeWidgetItem*, Node> guiNodes, Files;
    std::map<std::string, int> selectedItemCounter;
    bool calledFromChild;
    void loadNodes();

    void loadFilesInNode(std::string const nodeID, std::string const deletingDate);
    bool currFocusInDir = false;

    std::string currentNode;

    std::vector<std::string> getSelectedItems();
    void clearSelectection();
};

