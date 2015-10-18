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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessengerWindowClass
{
public:
    QWidget *centralWidget;
    QFrame *panel;
    QLabel *userPhoto;
    QLabel *userName;
    QPushButton *loginB;
    QPushButton *logoutB;
    QPushButton *newDialogB;
    QLabel *currentOponent;
    QFrame *dialogsInfoFrame;
    QScrollArea *dialogsInfoArea;
    QWidget *scrollAreaWidgetContents;
    QLineEdit *dialogSearch;
    QFrame *dialogFrame;
    QScrollArea *dialogArea;
    QWidget *scrollAreaWidgetContents_2;
    QTextEdit *message;
    QPushButton *sendMessageB;

    void setupUi(QMainWindow *MessengerWindowClass)
    {
        if (MessengerWindowClass->objectName().isEmpty())
            MessengerWindowClass->setObjectName(QStringLiteral("MessengerWindowClass"));
        MessengerWindowClass->resize(1100, 649);
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        MessengerWindowClass->setFont(font);
        centralWidget = new QWidget(MessengerWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        panel = new QFrame(centralWidget);
        panel->setObjectName(QStringLiteral("panel"));
        panel->setGeometry(QRect(0, 0, 1111, 50));
        QPalette palette;
        QBrush brush(QColor(86, 124, 164, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        panel->setPalette(palette);
        panel->setStyleSheet(QLatin1String("background-color: rgb(86, 124, 164);\n"
""));
        panel->setFrameShape(QFrame::Box);
        panel->setFrameShadow(QFrame::Sunken);
        userPhoto = new QLabel(panel);
        userPhoto->setObjectName(QStringLiteral("userPhoto"));
        userPhoto->setGeometry(QRect(0, 0, 50, 50));
        QPalette palette1;
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        userPhoto->setPalette(palette1);
        userPhoto->setFont(font);
        userName = new QLabel(panel);
        userName->setObjectName(QStringLiteral("userName"));
        userName->setGeometry(QRect(55, 0, 161, 50));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush);
        userName->setPalette(palette2);
        userName->setFont(font);
        loginB = new QPushButton(panel);
        loginB->setObjectName(QStringLiteral("loginB"));
        loginB->setGeometry(QRect(940, 10, 71, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Button, brush);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush);
        loginB->setPalette(palette3);
        loginB->setFont(font);
        logoutB = new QPushButton(panel);
        logoutB->setObjectName(QStringLiteral("logoutB"));
        logoutB->setGeometry(QRect(1020, 10, 71, 31));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Button, brush);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush);
        logoutB->setPalette(palette4);
        logoutB->setFont(font);
        newDialogB = new QPushButton(panel);
        newDialogB->setObjectName(QStringLiteral("newDialogB"));
        newDialogB->setGeometry(QRect(230, 0, 50, 50));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Button, brush);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush);
        newDialogB->setPalette(palette5);
        QFont font1;
        font1.setPointSize(24);
        newDialogB->setFont(font1);
        newDialogB->setFlat(true);
        currentOponent = new QLabel(panel);
        currentOponent->setObjectName(QStringLiteral("currentOponent"));
        currentOponent->setGeometry(QRect(580, 10, 181, 31));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette6.setBrush(QPalette::Active, QPalette::Button, brush);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette6.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush);
        currentOponent->setPalette(palette6);
        currentOponent->setFont(font);
        currentOponent->setAlignment(Qt::AlignCenter);
        dialogsInfoFrame = new QFrame(centralWidget);
        dialogsInfoFrame->setObjectName(QStringLiteral("dialogsInfoFrame"));
        dialogsInfoFrame->setGeometry(QRect(-2, 50, 281, 600));
        dialogsInfoFrame->setFrameShape(QFrame::Box);
        dialogsInfoFrame->setFrameShadow(QFrame::Raised);
        dialogsInfoArea = new QScrollArea(dialogsInfoFrame);
        dialogsInfoArea->setObjectName(QStringLiteral("dialogsInfoArea"));
        dialogsInfoArea->setGeometry(QRect(0, 30, 271, 571));
        dialogsInfoArea->setFrameShape(QFrame::NoFrame);
        dialogsInfoArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 271, 571));
        dialogsInfoArea->setWidget(scrollAreaWidgetContents);
        dialogSearch = new QLineEdit(dialogsInfoFrame);
        dialogSearch->setObjectName(QStringLiteral("dialogSearch"));
        dialogSearch->setGeometry(QRect(5, 5, 271, 21));
        dialogSearch->setFont(font);
        dialogFrame = new QFrame(centralWidget);
        dialogFrame->setObjectName(QStringLiteral("dialogFrame"));
        dialogFrame->setGeometry(QRect(280, 50, 821, 601));
        dialogFrame->setFrameShape(QFrame::StyledPanel);
        dialogFrame->setFrameShadow(QFrame::Raised);
        dialogArea = new QScrollArea(dialogFrame);
        dialogArea->setObjectName(QStringLiteral("dialogArea"));
        dialogArea->setGeometry(QRect(0, 0, 821, 561));
        dialogArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 819, 559));
        dialogArea->setWidget(scrollAreaWidgetContents_2);
        message = new QTextEdit(dialogFrame);
        message->setObjectName(QStringLiteral("message"));
        message->setGeometry(QRect(0, 560, 721, 38));
        message->setFont(font);
        sendMessageB = new QPushButton(dialogFrame);
        sendMessageB->setObjectName(QStringLiteral("sendMessageB"));
        sendMessageB->setGeometry(QRect(720, 560, 101, 39));
        sendMessageB->setFont(font);
        MessengerWindowClass->setCentralWidget(centralWidget);

        retranslateUi(MessengerWindowClass);

        QMetaObject::connectSlotsByName(MessengerWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MessengerWindowClass)
    {
        MessengerWindowClass->setWindowTitle(QApplication::translate("MessengerWindowClass", "MessengerWindow", 0));
        userPhoto->setText(QApplication::translate("MessengerWindowClass", "\320\244\320\276\321\202\320\276", 0));
        userName->setText(QApplication::translate("MessengerWindowClass", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217 \320\230\320\274\321\217", 0));
        loginB->setText(QApplication::translate("MessengerWindowClass", "\320\222\320\276\320\271\321\202\320\270", 0));
        logoutB->setText(QApplication::translate("MessengerWindowClass", "\320\222\321\213\320\271\321\202\320\270", 0));
        newDialogB->setText(QApplication::translate("MessengerWindowClass", "+", 0));
        currentOponent->setText(QApplication::translate("MessengerWindowClass", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \321\201\320\276\320\261\320\265\321\201\320\265\320\264\320\275\320\270\320\272", 0));
        dialogSearch->setPlaceholderText(QApplication::translate("MessengerWindowClass", "\320\237\320\276\320\270\321\201\320\272...", 0));
        message->setPlaceholderText(QApplication::translate("MessengerWindowClass", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265...", 0));
        sendMessageB->setText(QApplication::translate("MessengerWindowClass", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class MessengerWindowClass: public Ui_MessengerWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSENGERWINDOW_H
