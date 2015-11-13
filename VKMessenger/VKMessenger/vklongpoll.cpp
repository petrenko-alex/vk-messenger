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

QString VKLongPoll::getAttachmentsString(QJsonObject &attachments)
{
	int i = 1;
	QString attachmentsStr = "";
	QString next = "attach" + QString::number(i) + "_type";

	while (!attachments[next].toString().isEmpty())
	{
		attachmentsStr += attachments[next].toString() + ", ";
		++i;
		next = "attach" + QString::number(i) + "_type";
	}

	if (!attachmentsStr.isEmpty())
	{
		attachmentsStr.prepend("Вложения: ");
		attachmentsStr.remove(attachmentsStr.size() - 2, 2);
	}

	return attachmentsStr;
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
							QString text = u[6].toString();
							QString fromId = QString::number(u[3].toInt());
							MessageType type = MessageType::TEXT_MESSAGE;

							/* Обработка прикреплений */ 
							QString attachments = "";
							if (u[7].isObject())
							{
								QJsonObject attachment = u[7].toObject();
								if (text.isEmpty() && (attachment["attach1_type"].toString() == "sticker"))
								{
									type = MessageType::STICKER_MESSAGE;
									text = attachment["attach1"].toString();
								}
								else if (! attachment["attach1_type"].toString().isEmpty())
								{
									attachments = getAttachmentsString(u[7].toObject());
								}
								
								if (! attachment["fwd"].toString().isEmpty())
								{
									attachments += "\nПересланные сообщения";
								}
							}
							

							if (!attachments.isEmpty())
							{
								if (! text.isEmpty())
								{
									attachments.prepend("\n");
								}
								text += attachments;
							}

							emit messageReceived(type, fromId, text);
						}
					}
				}
			}
		}
	}
	emit tracingStopped();
}
