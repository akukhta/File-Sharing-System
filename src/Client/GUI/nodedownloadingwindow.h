#pragma once
#include <QWidget>
#include <memory>
#include "ClientInterface.h"

namespace Ui {
class NodeDownloadingWindow;
}

class NodeDownloadingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NodeDownloadingWindow(std::shared_ptr<ClientInterface> &clientInterface, QWidget *parent = nullptr);
    ~NodeDownloadingWindow();

private:
    Ui::NodeDownloadingWindow *ui;
    std::shared_ptr<ClientInterface> clientInterface;
};
