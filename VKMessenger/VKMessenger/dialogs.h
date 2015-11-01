#ifndef DIALOGS_H
#define DIALOGS_H

#include <QObject>
#include <QPair>
#include <QJsonDocument>
#include "session.h"
#include "vkdatareceiver.h"
#include "dialoginfo.h"

#define DIALOGS_COUNT 1

class Dialogs : public QObject
{
	Q_OBJECT

signals:
	void dialogLoaded(DialogInfo *dialogInfo);

public:
	Dialogs(Session &currentSession);
	~Dialogs();

	void setConnections();
	void loadDialogs();

private slots:
	void dialogsReceived(const QByteArray &userDialogs);

private:
	Session *currentSession;
	VKDataReceiver *dataReceiver;
	QHash<unsigned int, DialogInfo *> userDialogs;
};

#endif // DIALOGS_H
