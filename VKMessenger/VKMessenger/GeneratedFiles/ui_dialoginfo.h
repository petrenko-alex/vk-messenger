/********************************************************************************
** Form generated from reading UI file 'dialoginfo.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGINFO_H
#define UI_DIALOGINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogInfo
{
public:
    QGridLayout *gridLayout_2;
    QWidget *dialogInfo;
    QGridLayout *gridLayout;
    QLabel *photo;
    QFrame *line_2;
    QTextEdit *lastMessage;
    QLabel *name;
    QDateTimeEdit *lastMessageDateTime;

    void setupUi(QWidget *DialogInfo)
    {
        if (DialogInfo->objectName().isEmpty())
            DialogInfo->setObjectName(QStringLiteral("DialogInfo"));
        DialogInfo->resize(250, 100);
        DialogInfo->setStyleSheet(QLatin1String("QWidget#dialogInfo {\n"
"	border: 1px solid white;\n"
"	border-radius: 10px;\n"
"}"));
        gridLayout_2 = new QGridLayout(DialogInfo);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        dialogInfo = new QWidget(DialogInfo);
        dialogInfo->setObjectName(QStringLiteral("dialogInfo"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dialogInfo->sizePolicy().hasHeightForWidth());
        dialogInfo->setSizePolicy(sizePolicy);
        dialogInfo->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(dialogInfo);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        photo = new QLabel(dialogInfo);
        photo->setObjectName(QStringLiteral("photo"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(photo->sizePolicy().hasHeightForWidth());
        photo->setSizePolicy(sizePolicy1);
        photo->setMinimumSize(QSize(40, 40));
        photo->setMaximumSize(QSize(40, 40));
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        photo->setFont(font);
        photo->setStyleSheet(QLatin1String("QLabel {\n"
"	border: 3px solid #b0c4de;\n"
"	border-radius: 5px;\n"
"\n"
"}"));
        photo->setFrameShape(QFrame::Panel);
        photo->setFrameShadow(QFrame::Sunken);
        photo->setScaledContents(true);

        gridLayout->addWidget(photo, 0, 0, 2, 1);

        line_2 = new QFrame(dialogInfo);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setStyleSheet(QStringLiteral("QFrame#line_2 {color:white;}"));
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setFrameShape(QFrame::HLine);

        gridLayout->addWidget(line_2, 2, 0, 1, 3);

        lastMessage = new QTextEdit(dialogInfo);
        lastMessage->setObjectName(QStringLiteral("lastMessage"));
        lastMessage->setMinimumSize(QSize(0, 30));
        lastMessage->setMaximumSize(QSize(16777215, 30));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        lastMessage->setPalette(palette);
        QFont font1;
        font1.setFamily(QStringLiteral("Verdana"));
        font1.setPointSize(7);
        lastMessage->setFont(font1);
        lastMessage->setStyleSheet(QStringLiteral(""));
        lastMessage->setFrameShape(QFrame::NoFrame);
        lastMessage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        lastMessage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        lastMessage->setReadOnly(true);
        lastMessage->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        gridLayout->addWidget(lastMessage, 1, 1, 1, 2);

        name = new QLabel(dialogInfo);
        name->setObjectName(QStringLiteral("name"));
        sizePolicy1.setHeightForWidth(name->sizePolicy().hasHeightForWidth());
        name->setSizePolicy(sizePolicy1);
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        name->setPalette(palette1);
        name->setFont(font1);

        gridLayout->addWidget(name, 0, 1, 1, 1);

        lastMessageDateTime = new QDateTimeEdit(dialogInfo);
        lastMessageDateTime->setObjectName(QStringLiteral("lastMessageDateTime"));
        lastMessageDateTime->setMinimumSize(QSize(0, 10));
        lastMessageDateTime->setMaximumSize(QSize(45, 16777215));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        lastMessageDateTime->setPalette(palette2);
        lastMessageDateTime->setFont(font1);
        lastMessageDateTime->setStyleSheet(QStringLiteral("QDateTimeEdit {color: white;}"));
        lastMessageDateTime->setWrapping(false);
        lastMessageDateTime->setFrame(false);
        lastMessageDateTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lastMessageDateTime->setReadOnly(true);
        lastMessageDateTime->setButtonSymbols(QAbstractSpinBox::NoButtons);

        gridLayout->addWidget(lastMessageDateTime, 0, 2, 1, 1);


        gridLayout_2->addWidget(dialogInfo, 0, 0, 1, 1);


        retranslateUi(DialogInfo);

        QMetaObject::connectSlotsByName(DialogInfo);
    } // setupUi

    void retranslateUi(QWidget *DialogInfo)
    {
        DialogInfo->setWindowTitle(QApplication::translate("DialogInfo", "DialogInfo", 0));
        photo->setText(QApplication::translate("DialogInfo", "Photo", 0));
        name->setText(QApplication::translate("DialogInfo", "Name", 0));
        lastMessageDateTime->setDisplayFormat(QApplication::translate("DialogInfo", "dd.MM.yyyy \320\262 H:mm", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogInfo: public Ui_DialogInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGINFO_H
