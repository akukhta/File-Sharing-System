#pragma once

#include <QDialog>
#include <memory>
#include <vector>
#include "ClientInterface.h"
#include "Common/Node.h"

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

private:
    Ui::NodesWindow *ui;
    std::vector<Node> nodes;
    void addNode(std::string nodeID);
    std::shared_ptr<ClientInterface> clientInterface;
};

