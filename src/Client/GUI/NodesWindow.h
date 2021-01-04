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
    explicit NodesWindow(std::shared_ptr<ClientInterface>& clientInterface, QWidget *parent = nullptr);
    ~NodesWindow();

private:
    Ui::NodesWindow *ui;
    std::vector<Node> nodes;
    void addNode(std::string nodeID);
};

