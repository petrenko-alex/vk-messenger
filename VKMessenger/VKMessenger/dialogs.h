#ifndef DIALOGS_H
#define DIALOGS_H

#include <QObject>
#include <QPair>
#include <QJsonDocument>
#include "session.h"
#include "vkdatareceiver.h"
#include "dialoginfo.h"

#define DIALOGS_COUNT 20

class Dialogs : public QObject
{
	Q_OBJECT

signals:
	void dialogLoaded(DialogInfo *dialogInfo);

public:
	Dialogs();
	~Dialogs();

	void setConnections();
	void loadDialogs();

private slots:
	void dialogsReceived(const QByteArray &userDialogsData);

private:
	VKDataReceiver *dataReceiver;
	QList<DialogInfo *> userDialogs;
};

#endif // DIALOGS_H
