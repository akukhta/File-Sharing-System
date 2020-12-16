/********************************************************************************
** Form generated from reading UI file 'StartingWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTINGWINDOW_H
#define UI_STARTINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartingWindow
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *signUpBtn;
    QPushButton *logInBtn;
    QPushButton *getNodeBtn;

    void setupUi(QWidget *StartingWindow)
    {
        if (StartingWindow->objectName().isEmpty())
            StartingWindow->setObjectName(QString::fromUtf8("StartingWindow"));
        StartingWindow->resize(296, 120);
        gridLayout = new QGridLayout(StartingWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        signUpBtn = new QPushButton(StartingWindow);
        signUpBtn->setObjectName(QString::fromUtf8("signUpBtn"));

        verticalLayout->addWidget(signUpBtn);

        logInBtn = new QPushButton(StartingWindow);
        logInBtn->setObjectName(QString::fromUtf8("logInBtn"));

        verticalLayout->addWidget(logInBtn);

        getNodeBtn = new QPushButton(StartingWindow);
        getNodeBtn->setObjectName(QString::fromUtf8("getNodeBtn"));

        verticalLayout->addWidget(getNodeBtn);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(StartingWindow);

        QMetaObject::connectSlotsByName(StartingWindow);
    } // setupUi

    void retranslateUi(QWidget *StartingWindow)
    {
        StartingWindow->setWindowTitle(QApplication::translate("StartingWindow", "Authorization", nullptr));
        signUpBtn->setText(QApplication::translate("StartingWindow", "Sign up", nullptr));
        logInBtn->setText(QApplication::translate("StartingWindow", "Log in", nullptr));
        getNodeBtn->setText(QApplication::translate("StartingWindow", "Get a node", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartingWindow: public Ui_StartingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTINGWINDOW_H
