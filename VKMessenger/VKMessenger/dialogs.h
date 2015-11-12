#ifndef DIALOGS_H
#define DIALOGS_H

#include <QObject>
#include <QPair>
#include <QSound>
#include <QJsonDocument>
#include <QMessageBox>
#include "session.h"
#include "vkdatareceiver.h"
#include "dialoginfo.h"
#include "vklongpoll.h"

#define DIALOGS_COUNT 20
#define NOTIFICATION_SOUND_PATH "./Application Resources/Sounds/new_message.wav"

class Dialogs : public QObject
{
	Q_OBJECT

signals:
	void changeDialogPosition(QWidget *widget);
	void dialogsLoaded(QList<DialogInfo *> *userDialogs);
	void messagesLoaded(QWidget *scrollWidget, QString &username);
	void canExit();

public:
	Dialogs();
	~Dialogs();

	void loadDialogs();

private slots:
	void messagesReceived(QWidget *scrollWidget, QString &username);
	void addMessage(MessageType type,const QString &fromId, const QString &text);
	void stopTracing();
	void tracingStopped();
	void newMessage(QString &msg);
	void newDialog(unsigned int userId);
	void messageWasSent(QWidget *dialog);

private:
	void setConnections();
	bool getDialogs(unsigned int count);
	void parseDialogs(const QByteArray &userDialogsData);
	bool isChat(const QString &id);

	VKDataReceiver *dataReceiver;
	VKLongPoll *longPollConnection;
	QList<DialogInfo *> userDialogs;
};

#endif // DIALOGS_H
