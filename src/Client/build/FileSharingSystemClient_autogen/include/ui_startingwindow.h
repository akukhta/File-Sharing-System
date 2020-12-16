/********************************************************************************
** Form generated from reading UI file 'startingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTINGWINDOW_H
#define UI_STARTINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_StartingWindow
{
public:
    QGridLayout *gridLayout;
    QPushButton *signInButton;
    QPushButton *logInButton;
    QPushButton *pushButton_3;

    void setupUi(QDialog *StartingWindow)
    {
        if (StartingWindow->objectName().isEmpty())
            StartingWindow->setObjectName(QString::fromUtf8("StartingWindow"));
        StartingWindow->resize(400, 119);
        gridLayout = new QGridLayout(StartingWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        signInButton = new QPushButton(StartingWindow);
        signInButton->setObjectName(QString::fromUtf8("signInButton"));

        gridLayout->addWidget(signInButton, 0, 0, 1, 1);

        logInButton = new QPushButton(StartingWindow);
        logInButton->setObjectName(QString::fromUtf8("logInButton"));

        gridLayout->addWidget(logInButton, 1, 0, 1, 1);

        pushButton_3 = new QPushButton(StartingWindow);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 2, 0, 1, 1);


        retranslateUi(StartingWindow);

        QMetaObject::connectSlotsByName(StartingWindow);
    } // setupUi

    void retranslateUi(QDialog *StartingWindow)
    {
        StartingWindow->setWindowTitle(QApplication::translate("StartingWindow", "File Sharing ", nullptr));
        signInButton->setText(QApplication::translate("StartingWindow", "Sign In", nullptr));
        logInButton->setText(QApplication::translate("StartingWindow", "Log in", nullptr));
        pushButton_3->setText(QApplication::translate("StartingWindow", "Download a node", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartingWindow: public Ui_StartingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTINGWINDOW_H
