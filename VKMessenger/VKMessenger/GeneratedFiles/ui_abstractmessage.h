/********************************************************************************
** Form generated from reading UI file 'abstractmessage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABSTRACTMESSAGE_H
#define UI_ABSTRACTMESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AbstractMessage
{
public:

    void setupUi(QWidget *AbstractMessage)
    {
        if (AbstractMessage->objectName().isEmpty())
            AbstractMessage->setObjectName(QStringLiteral("AbstractMessage"));
        AbstractMessage->resize(94, 33);

        retranslateUi(AbstractMessage);

        QMetaObject::connectSlotsByName(AbstractMessage);
    } // setupUi

    void retranslateUi(QWidget *AbstractMessage)
    {
        AbstractMessage->setWindowTitle(QApplication::translate("AbstractMessage", "AbstractMessage", 0));
    } // retranslateUi

};

namespace Ui {
    class AbstractMessage: public Ui_AbstractMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABSTRACTMESSAGE_H
