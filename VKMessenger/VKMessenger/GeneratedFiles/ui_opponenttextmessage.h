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
#include <QtWidgets/QSpacerItem>
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
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *OpponentTextMessage)
    {
        if (OpponentTextMessage->objectName().isEmpty())
            OpponentTextMessage->setObjectName(QStringLiteral("OpponentTextMessage"));
        OpponentTextMessage->resize(407, 86);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OpponentTextMessage->sizePolicy().hasHeightForWidth());
        OpponentTextMessage->setSizePolicy(sizePolicy);
        OpponentTextMessage->setMinimumSize(QSize(407, 86));
        OpponentTextMessage->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        OpponentTextMessage->setFont(font);
        OpponentTextMessage->setStyleSheet(QStringLiteral("QTextEdit#message							{  border: 0px solid  white; border-radius: 10px;}"));
        gridLayout = new QGridLayout(OpponentTextMessage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame = new QWidget(OpponentTextMessage);
        frame->setObjectName(QStringLiteral("frame"));
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

        message = new QTextEdit(frame);
        message->setObjectName(QStringLiteral("message"));
        message->setMinimumSize(QSize(200, 40));
        message->setMaximumSize(QSize(16777215, 16777215));
        QPalette palette;
        QBrush brush(QColor(240, 240, 240, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        message->setPalette(palette);
        QFont font1;
        font1.setFamily(QStringLiteral("Verdana"));
        font1.setStyleStrategy(QFont::PreferAntialias);
        message->setFont(font1);
        message->setFrameShape(QFrame::NoFrame);
        message->setLineWidth(1);
        message->setUndoRedoEnabled(false);
        message->setReadOnly(true);

        horizontalLayout->addWidget(message);


        gridLayout->addWidget(frame, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);


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
