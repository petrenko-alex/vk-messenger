#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QWidget>
#include <QDateTime>
#include <QUrl>
#include <QJsonDocument>
#include "ui_dialoginfo.h"
#include "vkdatareceiver.h"

class DialogInfo : public QWidget
{
	Q_OBJECT

public:
	DialogInfo(QWidget *parent = 0);
	DialogInfo(const QString &userId, const QString &lastMessage);
	~DialogInfo();

private:
	Ui::DialogInfo ui;
	unsigned int userId;
	QString username;
	QString lastMessage;
	QDateTime lastMessageDateTime;
	/* Добавить фото */
};

#endif // DIALOGINFO_H
