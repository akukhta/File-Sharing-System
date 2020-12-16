#pragma once
#include <QDialog>
#include <memory>
#include "BL/ClientInterface.h"
#include "GUI/authorizationwindow.h"

namespace Ui {
class StartingWindow;
}

class StartingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartingWindow(std::shared_ptr<ClientInterface> &clientInterface, QWidget *parent = nullptr);
    ~StartingWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_signInButton_clicked();

    void on_logInButton_clicked();

private:
    Ui::StartingWindow *ui;
    std::shared_ptr<ClientInterface> clientInterface;
};

