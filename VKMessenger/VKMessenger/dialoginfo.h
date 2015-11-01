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
	DialogInfo( /*QWidget *parent, */
			    unsigned int userId,unsigned int messageId,
				QString &title,QString &lastMessage,
				QDateTime &lastMessageDateTime, bool out);
	~DialogInfo();
	DialogInfo & operator=(const DialogInfo &other);

private:
	Ui::DialogInfo ui;
	unsigned int userId;
	unsigned int messageId;
	QString title;
	QString username;
	QString lastMessage;
	QDateTime lastMessageDateTime;
	bool out;
	/* Добавить фото */
};

#endif // DIALOGINFO_H
