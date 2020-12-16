/********************************************************************************
** Form generated from reading UI file 'authorizationwindow.ui'
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
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AuthorizationWindow
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *emaiLbl;
    QLineEdit *email_edit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *passLbl;
    QLineEdit *pass_edit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *passConLbl;
    QLineEdit *passConf_edit;
    QCheckBox *stayInBox;
    QPushButton *logBtn;

    void setupUi(QDialog *AuthorizationWindow)
    {
        if (AuthorizationWindow->objectName().isEmpty())
            AuthorizationWindow->setObjectName(QString::fromUtf8("AuthorizationWindow"));
        AuthorizationWindow->resize(451, 209);
        gridLayout = new QGridLayout(AuthorizationWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        emaiLbl = new QLabel(AuthorizationWindow);
        emaiLbl->setObjectName(QString::fromUtf8("emaiLbl"));

        horizontalLayout->addWidget(emaiLbl);

        email_edit = new QLineEdit(AuthorizationWindow);
        email_edit->setObjectName(QString::fromUtf8("email_edit"));

        horizontalLayout->addWidget(email_edit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        passLbl = new QLabel(AuthorizationWindow);
        passLbl->setObjectName(QString::fromUtf8("passLbl"));

        horizontalLayout_2->addWidget(passLbl);

        pass_edit = new QLineEdit(AuthorizationWindow);
        pass_edit->setObjectName(QString::fromUtf8("pass_edit"));

        horizontalLayout_2->addWidget(pass_edit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        passConLbl = new QLabel(AuthorizationWindow);
        passConLbl->setObjectName(QString::fromUtf8("passConLbl"));

        horizontalLayout_3->addWidget(passConLbl);

        passConf_edit = new QLineEdit(AuthorizationWindow);
        passConf_edit->setObjectName(QString::fromUtf8("passConf_edit"));

        horizontalLayout_3->addWidget(passConf_edit);


        verticalLayout->addLayout(horizontalLayout_3);

        stayInBox = new QCheckBox(AuthorizationWindow);
        stayInBox->setObjectName(QString::fromUtf8("stayInBox"));

        verticalLayout->addWidget(stayInBox);

        logBtn = new QPushButton(AuthorizationWindow);
        logBtn->setObjectName(QString::fromUtf8("logBtn"));

        verticalLayout->addWidget(logBtn);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(AuthorizationWindow);

        QMetaObject::connectSlotsByName(AuthorizationWindow);
    } // setupUi

    void retranslateUi(QDialog *AuthorizationWindow)
    {
        AuthorizationWindow->setWindowTitle(QApplication::translate("AuthorizationWindow", "Authorization", nullptr));
        emaiLbl->setText(QApplication::translate("AuthorizationWindow", "Email:", nullptr));
        passLbl->setText(QApplication::translate("AuthorizationWindow", "Password:", nullptr));
        passConLbl->setText(QApplication::translate("AuthorizationWindow", "Confirm password:", nullptr));
        stayInBox->setText(QApplication::translate("AuthorizationWindow", "Stay signed in", nullptr));
        logBtn->setText(QApplication::translate("AuthorizationWindow", "Sign in", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthorizationWindow: public Ui_AuthorizationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORIZATIONWINDOW_H
