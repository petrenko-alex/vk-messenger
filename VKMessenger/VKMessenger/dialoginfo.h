#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QWidget>
#include <QDateTime>
#include "ui_dialoginfo.h"

class DialogInfo : public QWidget
{
	Q_OBJECT

public:
	DialogInfo(QWidget *parent = 0);
	DialogInfo(const QString &userId, const QString &lastMessage);
	~DialogInfo();

private:
	Ui::DialogInfo ui;
	QString username;
	QString lastMessage;
	QDateTime lastMessageDateTime;
	/* Добавить фото */
};

#endif // DIALOGINFO_H
