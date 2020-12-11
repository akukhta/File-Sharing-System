#ifndef STARTINGWINDOW_H
#define STARTINGWINDOW_H

#include <QWidget>
#include "AuthorizationWindow.h"

namespace Ui {
class StartingWindow;
}

class StartingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartingWindow(QWidget *parent = nullptr);
    ~StartingWindow();

private slots:
    void on_signUpBtn_clicked();

private:
    Ui::StartingWindow *ui;
};

#endif // STARTINGWINDOW_H
