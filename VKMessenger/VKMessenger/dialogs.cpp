#include "dialogs.h"

Dialogs::Dialogs()
{
	dataReceiver = new VKDataReceiver;
	longPollConnection = new VKLongPoll(this);
	setConnections();
}

Dialogs::~Dialogs()
{
	delete dataReceiver;
	delete longPollConnection;
}

void Dialogs::setConnections()
{
	// #TODO: Метод пуст!
}

void Dialogs::loadDialogs()
{
	/* Формируем запрос на получение диалогов */
	QList<QPair<QString, QString> > parametres;
	parametres << QPair<QString, QString>("count", QString::number(DIALOGS_COUNT));
	parametres << QPair<QString, QString>("v", "5.37");
	parametres << QPair<QString, QString>("access_token", QString(Session::getInstance ().get ("accessToken")));
	/* Посылаем запрос, получаем данные */
	QByteArray dialogs = dataReceiver->loadData("messages.getDialogs", parametres);

	if (!dialogs.isEmpty())
	{
		parseDialogs(dialogs);
	}
	else
	{
		QMessageBox::critical(0, "Ошибка соединения", "Не удалось получить список диалогов. Пожалуйста, проверьте интернет соединение.");
	}

	emit dialogsLoaded(&userDialogs);

	/* Последний диалог как текущий */
	userDialogs[0]->loadMessages();

	/* Устанавливаем Long Poll соединение */
	longPollConnection->getLongPollServer();
	longPollConnection->trace();
}

void Dialogs::messagesReceived(QWidget *scrollWidget, QString &username)
{
	emit messagesLoaded(scrollWidget,username);
}

void Dialogs::parseDialogs(const QByteArray &userDialogsData)
{
	DialogType dialogType;
	QString idKey;
	QJsonObject userDialogsObject = QJsonDocument::fromJson(userDialogsData).object();
	QJsonArray userDialogsArray =  userDialogsObject.value("response").toObject()["items"].toArray ();
	
	for (auto dialog : userDialogsArray)
	{
		QJsonObject dialogInfo = dialog.toObject()["message"].toObject();

		if (dialogInfo.contains("chat_id"))
		{
			/* Если диалог принадлежит чату */
			dialogType = DialogType::CHAT;
			idKey = "chat_id";
		}
		else
		{
			/* Если диалог персональный */
			dialogType = DialogType::PERSONAL;
			idKey = "user_id";
		}

		QString lastMessage = dialogInfo["body"].toString();
		if (lastMessage.isEmpty())
		{
			lastMessage = "Вложение: ";
			lastMessage += dialogInfo["attachments"].toArray()[0].toObject()["type"].toString();
		}

		DialogInfo *d = new DialogInfo( dialogType,
										dialogInfo[idKey].toInt(), dialogInfo["id"].toInt(),
										dialogInfo["title"].toString(), lastMessage,
										QDateTime::fromTime_t(dialogInfo["date"].toInt()), dialogInfo["out"].toInt());

		connect(d, SIGNAL(messagesLoaded(QWidget *, QString &)), this, SLOT(messagesReceived(QWidget *, QString &)));

		userDialogs << d;
		d->loadOpponentInfo();
	}
}
