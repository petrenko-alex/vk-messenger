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
	connect(longPollConnection, SIGNAL(tracingStopped()), this, SLOT(tracingStopped()));
	connect(longPollConnection, SIGNAL(messageReceived(MessageType,const QString &, const QString &)), this, SLOT(addMessage(MessageType,const QString &, const QString &)));
}

bool Dialogs::getDialogs(unsigned int count)
{
	/* Формируем запрос на получение диалогов */
	QList<QPair<QString, QString> > parametres;
	parametres << QPair<QString, QString>("count", QString::number(count));
	parametres << QPair<QString, QString>("v", "5.37");
	parametres << QPair<QString, QString>("access_token", QString(Session::getInstance().get("accessToken")));
	/* Посылаем запрос, получаем данные */
	QByteArray dialogs = dataReceiver->loadData("messages.getDialogs", parametres);

	if (!dialogs.isEmpty())
	{
		parseDialogs(dialogs);
	}
	else
	{
		QMessageBox::critical(0, "Ошибка соединения", "Не удалось получить список диалогов. Пожалуйста, проверьте интернет соединение.");
		return false;
	}
	return true;
}

void Dialogs::loadDialogs()
{
	if (getDialogs(DIALOGS_COUNT))
	{
		emit dialogsLoaded(&userDialogs);

		/* Последний диалог как текущий */
		userDialogs[0]->loadMessages();
		Session::getInstance().setCurrentOpponent(userDialogs[0]->getId().toInt ());

		/* Устанавливаем Long Poll соединение */
		longPollConnection->getLongPollServer();
		longPollConnection->startTracing();
	}
}

void Dialogs::messagesReceived(QWidget *scrollWidget, QString &username)
{
	emit messagesLoaded(scrollWidget,username);
}

void Dialogs::addMessage(MessageType type, const QString &fromId, const QString &text)
{
	bool dialogExist = false;

	/* Найти диалог */
	for (auto dialog : userDialogs)
	{
		if ((*dialog).getId() == fromId)
		{
			dialogExist = true;
			(*dialog).addMessage(type,fromId, text);

			if (type == MessageType::STICKER_MESSAGE)
			{
				(*dialog).setLastMessage("Вложение: sticker");
			}
			else if (type == MessageType::TEXT_MESSAGE)
			{
				(*dialog).setLastMessage(text);
			}
			
			emit changeDialogPosition(dialog);
			QSound::play(NOTIFICATION_SOUND_PATH);
		}
	}

	/* Если не найден - создать новый */
	if (!dialogExist)
	{
		QString idKey;
		if (isChat(fromId))
		{
			// #TODO: Создать новый чат
		}
		else
		{
			if (getDialogs(1))
			{
				userDialogs.last()->paintFrameRed();
				emit changeDialogPosition(userDialogs.last());
			}
		}
	}
}

void Dialogs::stopTracing()
{
	longPollConnection->stopTracing();
}

void Dialogs::tracingStopped()
{
	emit canExit();
}

void Dialogs::newMessage(QString &msg)
{
	DialogInfo *currentDialog;

	for (auto dialog : userDialogs)
	{
		if ((*dialog).getId().toInt() == Session::getInstance().getCurrentOpponent())
		{
			(*dialog).sendMessage(msg);
		}
	}
}

void Dialogs::newDialog(unsigned int userId)
{
	bool dialogExist = false;

	/* Ищем диалог в списке существующих */
	for (auto dialog : userDialogs)
	{
		if ((*dialog).getId().toInt() == userId)
		{
			dialogExist = true;
			emit changeDialogPosition(dialog);

			if ((*dialog).isInitialized())
			{
				messagesReceived((*dialog).getMessagesWidget(), (*dialog).getUserName());
			}
			else
			{
				(*dialog).loadMessages();
			}
		}
	}


	if (!dialogExist)
	{
		// #TODO: Реализовать
	}

}

void Dialogs::messageWasSent(QWidget *dialog)
{
	emit changeDialogPosition(dialog);
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
		if (dialogInfo["attachments"].isArray() && dialogInfo["attachments"].toArray()[0].isObject())
		{
			lastMessage += "\nВложения: ";
			lastMessage += dialogInfo["attachments"].toArray()[0].toObject()["type"].toString();
		}

		DialogInfo *d = new DialogInfo( dialogType,
										dialogInfo[idKey].toInt(), dialogInfo["id"].toInt(),
										dialogInfo["title"].toString(), lastMessage,
										QDateTime::fromTime_t(dialogInfo["date"].toInt()), dialogInfo["out"].toInt());

		connect(d, SIGNAL(messagesLoaded(QWidget *, QString &)), this, SLOT(messagesReceived(QWidget *, QString &)));
		connect(d, SIGNAL(messageWasSent(QWidget *)), this, SLOT(messageWasSent(QWidget *)));

		userDialogs << d;
		d->loadOpponentInfo();
	}
}

bool Dialogs::isChat(const QString &id)
{
	QList<QPair<QString, QString> > parametres;
	parametres << QPair<QString, QString>("chat_id", id);
	parametres << QPair<QString, QString>("v", "5.40");
	parametres << QPair<QString, QString>("access_token", QString(Session::getInstance().get("accessToken")));
	QByteArray response = dataReceiver->loadData("messages.getChat", parametres);
	if (!response.isEmpty())
	{
		QJsonObject dialog = QJsonDocument::fromJson(response).object();
		
		if (dialog.contains("error"))
		{
			return false;
		}
		else if (dialog.contains("response"))
		{
			return true;
		}
	}
	return false;
}
