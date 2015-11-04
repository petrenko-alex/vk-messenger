#include "dialogs.h"

Dialogs::Dialogs()
{
	dataReceiver = new VKDataReceiver;

	setConnections();
}

Dialogs::~Dialogs()
{
	delete dataReceiver;
}

void Dialogs::setConnections()
{
	connect(dataReceiver, SIGNAL(dataReceived(const QByteArray &)), this, SLOT(dialogsReceived(const QByteArray &)));
}

void Dialogs::loadDialogs()
{
	QList<QPair<QString, QString> > parametres;
	parametres << QPair<QString, QString>("count", QString::number(DIALOGS_COUNT));
	parametres << QPair<QString, QString>("v", "5.37");
	parametres << QPair<QString, QString>("access_token", QString(Session::getInstance ().get ("accessToken")));

	dataReceiver->sendRequest("messages.getDialogs", parametres);
}

void Dialogs::dialogsReceived(const QByteArray &userDialogsData)
{
	QJsonObject userDialogsObject = QJsonDocument::fromJson(userDialogsData).object();
	QJsonArray userDialogsArray =  userDialogsObject.value("response").toObject()["items"].toArray ();
	
	for (auto dialog : userDialogsArray)
	{
		QJsonObject dialogInfo = dialog.toObject()["message"].toObject();

		DialogInfo *d = new DialogInfo( dialogInfo["user_id"].toInt(), dialogInfo["id"].toInt(),
										dialogInfo["title"].toString(), dialogInfo["body"].toString(),
										QDateTime::fromTime_t(dialogInfo["date"].toInt()), dialogInfo["out"].toBool());

		userDialogs << d;
		emit dialogLoaded(d);
	}
}
