/********************************************************************************
** Form generated from reading UI file 'AuthorizationWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHORIZATIONWINDOW_H
#define UI_AUTHORIZATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthorizationWIndow
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *mailLbl;
    QLineEdit *mailEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *passwordLbl;
    QLineEdit *passEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *repeatPassLbl;
    QLineEdit *repeatPassEdit;
    QPushButton *authorizationBtn;
    QCheckBox *stayFlag;

    void setupUi(QWidget *AuthorizationWIndow)
    {
        if (AuthorizationWIndow->objectName().isEmpty())
            AuthorizationWIndow->setObjectName(QString::fromUtf8("AuthorizationWIndow"));
        AuthorizationWIndow->resize(400, 191);
        gridLayout = new QGridLayout(AuthorizationWIndow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mailLbl = new QLabel(AuthorizationWIndow);
        mailLbl->setObjectName(QString::fromUtf8("mailLbl"));

        horizontalLayout->addWidget(mailLbl);

        mailEdit = new QLineEdit(AuthorizationWIndow);
        mailEdit->setObjectName(QString::fromUtf8("mailEdit"));

        horizontalLayout->addWidget(mailEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        passwordLbl = new QLabel(AuthorizationWIndow);
        passwordLbl->setObjectName(QString::fromUtf8("passwordLbl"));

        horizontalLayout_2->addWidget(passwordLbl);

        passEdit = new QLineEdit(AuthorizationWIndow);
        passEdit->setObjectName(QString::fromUtf8("passEdit"));

        horizontalLayout_2->addWidget(passEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        repeatPassLbl = new QLabel(AuthorizationWIndow);
        repeatPassLbl->setObjectName(QString::fromUtf8("repeatPassLbl"));

        horizontalLayout_3->addWidget(repeatPassLbl);

        repeatPassEdit = new QLineEdit(AuthorizationWIndow);
        repeatPassEdit->setObjectName(QString::fromUtf8("repeatPassEdit"));

        horizontalLayout_3->addWidget(repeatPassEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        authorizationBtn = new QPushButton(AuthorizationWIndow);
        authorizationBtn->setObjectName(QString::fromUtf8("authorizationBtn"));

        verticalLayout->addWidget(authorizationBtn);

        stayFlag = new QCheckBox(AuthorizationWIndow);
        stayFlag->setObjectName(QString::fromUtf8("stayFlag"));

        verticalLayout->addWidget(stayFlag);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(AuthorizationWIndow);

        QMetaObject::connectSlotsByName(AuthorizationWIndow);
    } // setupUi

    void retranslateUi(QWidget *AuthorizationWIndow)
    {
        AuthorizationWIndow->setWindowTitle(QApplication::translate("AuthorizationWIndow", "Authorization", nullptr));
        mailLbl->setText(QApplication::translate("AuthorizationWIndow", "Email:", nullptr));
        passwordLbl->setText(QApplication::translate("AuthorizationWIndow", "Password:", nullptr));
        repeatPassLbl->setText(QApplication::translate("AuthorizationWIndow", "Confirm password:", nullptr));
        authorizationBtn->setText(QApplication::translate("AuthorizationWIndow", "Sign up", nullptr));
        stayFlag->setText(QApplication::translate("AuthorizationWIndow", "Stay signed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthorizationWIndow: public Ui_AuthorizationWIndow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORIZATIONWINDOW_H
