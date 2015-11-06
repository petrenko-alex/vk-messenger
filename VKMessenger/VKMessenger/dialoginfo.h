#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QWidget>
#include <QDateTime>
#include <QUrl>
#include <QMouseEvent>
#include <QJsonDocument>
#include "ui_dialoginfo.h"
#include "session.h"
#include <windows.h>
#include "vkdatareceiver.h"
#include "abstractmessage.h"
#include "usertextmessage.h"
#include "opponenttextmessage.h"

#define WIDTH  260
#define HEIGHT 100
#define MESSAGES_COUNT 100
#define GROUP_AVATAR_PATH "./Application Resources/group_avatar.png"

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
	void loadMessages();

signals:
	void messagesLoaded(QList<AbstractMessage *> *userMessages, QString &username);

private:
	void setConnections();
	void setDataToWidgets();
	void parseMessages(const QByteArray &messages);
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

	Ui::DialogInfo ui;
	unsigned int userId;
	unsigned int messageId;
	QString title;
	QString username;
	QString lastMessage;
	QDateTime lastMessageDateTime;
	QByteArray photo;
	bool out;
	VKDataReceiver *dataReceiver;

	QList<AbstractMessage *> userMessages;
	bool clicked;
};

#endif // DIALOGINFO_H
