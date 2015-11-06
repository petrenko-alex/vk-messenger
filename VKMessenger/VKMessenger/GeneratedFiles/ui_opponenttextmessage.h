/********************************************************************************
** Form generated from reading UI file 'opponenttextmessage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPPONENTTEXTMESSAGE_H
#define UI_OPPONENTTEXTMESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpponentTextMessage
{
public:
    QGridLayout *gridLayout;
    QWidget *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *photo;
    QTextEdit *message;

    void setupUi(QWidget *OpponentTextMessage)
    {
        if (OpponentTextMessage->objectName().isEmpty())
            OpponentTextMessage->setObjectName(QStringLiteral("OpponentTextMessage"));
        OpponentTextMessage->resize(504, 86);
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        OpponentTextMessage->setFont(font);
        gridLayout = new QGridLayout(OpponentTextMessage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame = new QWidget(OpponentTextMessage);
        frame->setObjectName(QStringLiteral("frame"));
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

        message = new QTextEdit(frame);
        message->setObjectName(QStringLiteral("message"));
        message->setMinimumSize(QSize(200, 40));
        message->setMaximumSize(QSize(16777215, 50));
        QPalette palette;
        QBrush brush(QColor(240, 240, 240, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        message->setPalette(palette);
        message->setFrameShape(QFrame::NoFrame);
        message->setLineWidth(0);

        horizontalLayout->addWidget(message);


        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(OpponentTextMessage);

        QMetaObject::connectSlotsByName(OpponentTextMessage);
    } // setupUi

    void retranslateUi(QWidget *OpponentTextMessage)
    {
        OpponentTextMessage->setWindowTitle(QApplication::translate("OpponentTextMessage", "OpponentTextMessage", 0));
        photo->setText(QApplication::translate("OpponentTextMessage", "Photo", 0));
    } // retranslateUi

};

namespace Ui {
    class OpponentTextMessage: public Ui_OpponentTextMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPPONENTTEXTMESSAGE_H
