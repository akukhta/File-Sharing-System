#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QWidget>

namespace Ui {
class AuthorizationWIndow;
}

class AuthorizationWIndow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorizationWIndow(bool isSignUp = false, QWidget *parent = nullptr);
    ~AuthorizationWIndow();

private:
    Ui::AuthorizationWIndow *ui;
};

#endif // AUTHORIZATIONWINDOW_H
