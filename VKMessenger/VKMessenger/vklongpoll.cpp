#include "vklongpoll.h"

VKLongPoll::VKLongPoll(QObject *parent)
	: QObject(parent)
{
	ts = "";
	key = "";
	pts = "";
	server = "";
	stopConnection = false;
}

VKLongPoll::~VKLongPoll()
{

}

void VKLongPoll::getLongPollServer()
{
	VKDataReceiver dataReceiver;
	QList<QPair<QString, QString> > parametres;
	parametres << QPair<QString, QString>("use_ssl", "0");
	parametres << QPair<QString, QString>("need_pts", "1");
	parametres << QPair<QString, QString>("v", "5.40");
	parametres << QPair<QString, QString>("access_token", Session::getInstance ().get ("accessToken"));

	QByteArray response = dataReceiver.loadData("messages.getLongPollServer", parametres);

	if (!response.isEmpty())
	{
		QJsonObject returnedData = QJsonDocument::fromJson(response).object()["response"].toObject();

		key = returnedData["key"].toString();
		server = returnedData["server"].toString();
		ts = QString::number(returnedData["ts"].toInt());
		pts = QString::number(returnedData["pts"].toInt());
	}
}

void VKLongPoll::stopTracing()
{
	stopConnection = true;
}

void VKLongPoll::startTracing()
{
	while (!stopConnection)
	{
		qDebug() << "Tracing Long Poll server ...";

		VKDataReceiver dataReceiver;
		QList<QPair<QString, QString> > parametres;
		parametres << QPair<QString, QString>("act", "a_check");
		parametres << QPair<QString, QString>("key", key);
		parametres << QPair<QString, QString>("ts", ts);
		parametres << QPair<QString, QString>("wait", "25");
		parametres << QPair<QString, QString>("mode", "2");

		QByteArray response = dataReceiver.longPollRequest("http://" + server,parametres);

		qDebug() << QString(response);

		if (!response.isEmpty())
		{
			QJsonObject returnedData = QJsonDocument::fromJson(response).object();
			
			ts = QString::number(returnedData["ts"].toInt());

			QJsonArray updates = returnedData["updates"].toArray();

			if (updates.size())
			{
				for (auto update : updates)
				{
					auto u = update.toArray();
					if (u[0].toInt() == EventType::NEW_MESSAGE)
					{
						int flags = u[2].toInt();
						int result = !(flags & 2);

						if (result)
						{
							QString fromId = QString::number(u[3].toInt());
							QString text = u[6].toString();

							// Обработать attachments 

							emit messageReceived(fromId, text);
						}
					}
				}
			}
		}
	}
	emit tracingStopped();
}
