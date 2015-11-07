/********************************************************************************
** Form generated from reading UI file 'stickermessage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STICKERMESSAGE_H
#define UI_STICKERMESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "abstractmessage.h"

QT_BEGIN_NAMESPACE

class Ui_UserStickerMessage
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QWidget *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *photo;
    QLabel *sticker;

    void setupUi(AbstractMessage *UserStickerMessage)
    {
        if (UserStickerMessage->objectName().isEmpty())
            UserStickerMessage->setObjectName(QStringLiteral("UserStickerMessage"));
        UserStickerMessage->resize(407, 167);
        UserStickerMessage->setMinimumSize(QSize(407, 167));
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        UserStickerMessage->setFont(font);
        horizontalLayout_2 = new QHBoxLayout(UserStickerMessage);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(196, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        frame = new QWidget(UserStickerMessage);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setStyleSheet(QLatin1String("QWidget#frame {\n"
"	border: 1px solid #567CA4;\n"
"	border-radius: 10px;\n"
"}"));
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        photo = new QLabel(frame);
        photo->setObjectName(QStringLiteral("photo"));
        photo->setMinimumSize(QSize(40, 40));
        photo->setMaximumSize(QSize(40, 40));
        photo->setStyleSheet(QLatin1String("QLabel {\n"
"	border: 3px solid #567CA4;\n"
"	border-radius: 5px;\n"
"\n"
"}"));

        horizontalLayout->addWidget(photo);

        sticker = new QLabel(frame);
        sticker->setObjectName(QStringLiteral("sticker"));
        sticker->setMinimumSize(QSize(120, 128));
        sticker->setMaximumSize(QSize(120, 128));

        horizontalLayout->addWidget(sticker);


        horizontalLayout_2->addWidget(frame);


        retranslateUi(UserStickerMessage);

        QMetaObject::connectSlotsByName(UserStickerMessage);
    } // setupUi

    void retranslateUi(AbstractMessage *UserStickerMessage)
    {
        UserStickerMessage->setWindowTitle(QApplication::translate("UserStickerMessage", "UserStickerMessage", 0));
        photo->setText(QApplication::translate("UserStickerMessage", "Photo", 0));
        sticker->setText(QApplication::translate("UserStickerMessage", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class UserStickerMessage: public Ui_UserStickerMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STICKERMESSAGE_H
