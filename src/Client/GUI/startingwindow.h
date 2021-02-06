#pragma once
#include <QDialog>
#include <QMessageBox>
#include <memory>
#include "ClientInterface.h"
#include "GUI/authorizationwindow.h"
#include "GUI/NodesWindow.h"

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
    void ErrorMessage(QString const &text, QString const &title);
};

