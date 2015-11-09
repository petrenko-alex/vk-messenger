#ifndef DIALOGS_H
#define DIALOGS_H

#include <QObject>
#include <QPair>
#include <QJsonDocument>
#include <QMessageBox>
#include "session.h"
#include "vkdatareceiver.h"
#include "dialoginfo.h"
#include "vklongpoll.h"

#define DIALOGS_COUNT 20

class Dialogs : public QObject
{
	Q_OBJECT

signals:
	void dialogsLoaded(QList<DialogInfo *> *userDialogs);
	void messagesLoaded(QWidget *scrollWidget, QString &username);

public:
	Dialogs();
	~Dialogs();

	void loadDialogs();

private slots:
	void messagesReceived(QWidget *scrollWidget, QString &username);

private:
	void setConnections();
	void parseDialogs(const QByteArray &userDialogsData);

	VKDataReceiver *dataReceiver;
	VKLongPoll *longPollConnection;
	QList<DialogInfo *> userDialogs;
};

#endif // DIALOGS_H
