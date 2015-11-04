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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogInfo
{
public:
    QGridLayout *gridLayout_2;
    QWidget *dialogInfo;
    QGridLayout *gridLayout;
    QLabel *photo;
    QLabel *name;
    QDateTimeEdit *lastMessageDateTime;
    QFrame *line_2;
    QLabel *lastMessage;

    void setupUi(QWidget *DialogInfo)
    {
        if (DialogInfo->objectName().isEmpty())
            DialogInfo->setObjectName(QStringLiteral("DialogInfo"));
        DialogInfo->resize(293, 111);
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

        gridLayout->addWidget(photo, 0, 0, 2, 1);

        name = new QLabel(dialogInfo);
        name->setObjectName(QStringLiteral("name"));
        sizePolicy1.setHeightForWidth(name->sizePolicy().hasHeightForWidth());
        name->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(name, 0, 1, 1, 1);

        lastMessageDateTime = new QDateTimeEdit(dialogInfo);
        lastMessageDateTime->setObjectName(QStringLiteral("lastMessageDateTime"));
        QFont font;
        font.setPointSize(7);
        lastMessageDateTime->setFont(font);
        lastMessageDateTime->setButtonSymbols(QAbstractSpinBox::NoButtons);

        gridLayout->addWidget(lastMessageDateTime, 0, 2, 1, 1);

        line_2 = new QFrame(dialogInfo);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShadow(QFrame::Raised);
        line_2->setFrameShape(QFrame::HLine);

        gridLayout->addWidget(line_2, 2, 0, 1, 3);

        lastMessage = new QLabel(dialogInfo);
        lastMessage->setObjectName(QStringLiteral("lastMessage"));
        sizePolicy1.setHeightForWidth(lastMessage->sizePolicy().hasHeightForWidth());
        lastMessage->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lastMessage, 1, 1, 1, 2);


        gridLayout_2->addWidget(dialogInfo, 0, 0, 1, 1);


        retranslateUi(DialogInfo);

        QMetaObject::connectSlotsByName(DialogInfo);
    } // setupUi

    void retranslateUi(QWidget *DialogInfo)
    {
        DialogInfo->setWindowTitle(QApplication::translate("DialogInfo", "DialogInfo", 0));
        photo->setText(QApplication::translate("DialogInfo", "Photo", 0));
        name->setText(QApplication::translate("DialogInfo", "Name", 0));
        lastMessage->setText(QApplication::translate("DialogInfo", "Last Message", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogInfo: public Ui_DialogInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGINFO_H
