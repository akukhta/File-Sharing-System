#pragma once
#include <QDialog>
#include <memory>
#include "BL/ClientInterface.h"

namespace Ui {
class AuthorizationWindow;
}

class AuthorizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(std::shared_ptr<ClientInterface>& clientInterface, bool isSigup = true,QWidget *parent = nullptr);
    ~AuthorizationWindow();
    std::string getEmail();
    std::string getPass();

private slots:
    void on_logBtn_clicked();

private:
    Ui::AuthorizationWindow *ui;
    std::shared_ptr<ClientInterface> clientInterface;
};
