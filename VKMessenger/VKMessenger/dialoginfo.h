#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QWidget>
#include <QDateTime>
#include <QUrl>
#include <QJsonDocument>
#include "ui_dialoginfo.h"
#include "session.h"
#include <windows.h>
#include "vkdatareceiver.h"

#define WIDTH  250
#define HEIGHT 100

class DialogInfo : public QWidget
{
	Q_OBJECT

public:
	DialogInfo( unsigned int userId,unsigned int messageId,
				QString &title,QString &lastMessage,
				QDateTime &lastMessageDateTime, bool out);
	~DialogInfo();
	DialogInfo & operator=(const DialogInfo &other);

	void loadOpponentInfo();
	void loadOpponentPhoto(QString photoUrl);

private:
	void setConnections();
	void setDataToWidgets();

	Ui::DialogInfo ui;
	unsigned int userId;
	unsigned int messageId;
	QString title;
	QString username;
	QString lastMessage;
	QDateTime lastMessageDateTime;
	bool out;
	VKDataReceiver *dataReceiver;
};

#endif // DIALOGINFO_H
