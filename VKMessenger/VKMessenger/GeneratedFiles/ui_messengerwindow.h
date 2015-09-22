/********************************************************************************
** Form generated from reading UI file 'messengerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSENGERWINDOW_H
#define UI_MESSENGERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessengerWindowClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MessengerWindowClass)
    {
        if (MessengerWindowClass->objectName().isEmpty())
            MessengerWindowClass->setObjectName(QStringLiteral("MessengerWindowClass"));
        MessengerWindowClass->resize(600, 400);
        menuBar = new QMenuBar(MessengerWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MessengerWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MessengerWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MessengerWindowClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MessengerWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MessengerWindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MessengerWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MessengerWindowClass->setStatusBar(statusBar);

        retranslateUi(MessengerWindowClass);

        QMetaObject::connectSlotsByName(MessengerWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MessengerWindowClass)
    {
        MessengerWindowClass->setWindowTitle(QApplication::translate("MessengerWindowClass", "MessengerWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class MessengerWindowClass: public Ui_MessengerWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSENGERWINDOW_H
