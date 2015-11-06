/********************************************************************************
** Form generated from reading UI file 'usertextmessage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERTEXTMESSAGE_H
#define UI_USERTEXTMESSAGE_H

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

class Ui_UserTextMessage
{
public:
    QGridLayout *gridLayout;
    QWidget *frame;
    QHBoxLayout *horizontalLayout;
    QTextEdit *message;
    QLabel *photo;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *UserTextMessage)
    {
        if (UserTextMessage->objectName().isEmpty())
            UserTextMessage->setObjectName(QStringLiteral("UserTextMessage"));
        UserTextMessage->resize(407, 86);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UserTextMessage->sizePolicy().hasHeightForWidth());
        UserTextMessage->setSizePolicy(sizePolicy);
        UserTextMessage->setMinimumSize(QSize(407, 86));
        UserTextMessage->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        UserTextMessage->setFont(font);
        UserTextMessage->setStyleSheet(QStringLiteral("QTextEdit#message							{  border: 0px solid  white; border-radius: 10px;}"));
        gridLayout = new QGridLayout(UserTextMessage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame = new QWidget(UserTextMessage);
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


        gridLayout->addWidget(frame, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);


        retranslateUi(UserTextMessage);

        QMetaObject::connectSlotsByName(UserTextMessage);
    } // setupUi

    void retranslateUi(QWidget *UserTextMessage)
    {
        UserTextMessage->setWindowTitle(QApplication::translate("UserTextMessage", "UserTextMessage", 0));
        message->setHtml(QApplication::translate("UserTextMessage", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Verdana'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        photo->setText(QApplication::translate("UserTextMessage", "Photo", 0));
    } // retranslateUi

};

namespace Ui {
    class UserTextMessage: public Ui_UserTextMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERTEXTMESSAGE_H
