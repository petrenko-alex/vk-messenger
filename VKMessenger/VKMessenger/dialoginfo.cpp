#include "dialoginfo.h"

DialogInfo::DialogInfo(unsigned int userId, unsigned int messageId, QString &title, QString &lastMessage, QDateTime &lastMessageDateTime, bool out)
{
	ui.setupUi(this);
	dataReceiver = new VKDataReceiver;
	setConnections();

	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->setMinimumSize(WIDTH, HEIGHT);


	this->userId = userId;
	this->messageId = messageId;
	this->title = title;
	this->lastMessage = lastMessage;
	this->lastMessageDateTime = lastMessageDateTime;
	this->out = out;

	setDataToWidgets();
	clicked = false;
}

DialogInfo::~DialogInfo()
{
	delete dataReceiver;
}

void DialogInfo::loadOpponentInfo()
{
	if (title == " ... ")
	{
		/* Загружаем информацию о собеседнике */
		QList<QPair<QString, QString> > parametres;
		parametres << QPair<QString, QString>("user_ids", QString::number(userId));
		parametres << QPair<QString, QString>("fields", "photo_50");
		parametres << QPair<QString, QString>("name_case", "Nom");
		parametres << QPair<QString, QString>("v", "5.37");
		parametres << QPair<QString, QString>("access_token", Session::getInstance().get("accessToken"));

		QByteArray userInfo = dataReceiver->sendRequest("users.get", parametres);
		if (!userInfo.isEmpty())
		{
			/* Получаем информацию о пользователе */
			QJsonObject userDataObject = QJsonDocument::fromJson(userInfo).object();
			QJsonValue userDataValue = userDataObject.value("response");
			QJsonArray userDataArray = userDataValue.toArray();
			QString userName = userDataArray[0].toObject().value("first_name").toString() + " " + userDataArray[0].toObject().value("last_name").toString();
			QString userPhoto = userDataArray[0].toObject().value("photo_50").toString();

			ui.name->setText(userName);
			this->username = userName;
			loadOpponentPhoto(userPhoto);
		}
		else
		{
			// #TODO: Решить что делать здесь.
		}
		
	}
	else
	{
		/* Имя группы */
		ui.name->setText(title);
	}
}

void DialogInfo::loadOpponentPhoto(QString photoUrl)
{
	QUrl userPhotoUrl(photoUrl);

	if (userPhotoUrl.isValid())
	{
		QByteArray userPhoto = dataReceiver->loadPhoto(QUrl(photoUrl));
		
		QPixmap photo;

		if (!userPhoto.isEmpty() && photo.loadFromData(userPhoto))
		{
			ui.photo->setPixmap(photo);
			this->photo = userPhoto;
		}
		else
		{
			// #TODO: Решить что делать здесь.
		}
	}
}

void DialogInfo::loadMessages()
{
	/* Формируем запрос на получение диалогов */
	QList<QPair<QString, QString> > parametres;
	parametres << QPair<QString, QString>("count", QString::number(MESSAGES_COUNT));
	parametres << QPair<QString, QString>("user_id", QString::number(userId));
	parametres << QPair<QString, QString>("v", "5.37");
	parametres << QPair<QString, QString>("access_token", Session::getInstance().get("accessToken"));
	/* Посылаем запрос, получаем данные */
	QByteArray messages = dataReceiver->sendRequest("messages.getHistory", parametres);

	if (!messages.isEmpty())
	{
		parseMessages(messages);
	}
}

void DialogInfo::parseMessages(const QByteArray &messages)
{
	QJsonObject dialogMessagessObject = QJsonDocument::fromJson(messages).object();
	QJsonArray dialogMessagesArray = dialogMessagessObject.value("response").toObject()["items"].toArray();

	for (auto msg : dialogMessagesArray)
	{
		bool out = msg.toObject()["out"].toInt();

		AbstractMessage *message;
		if (out)
		{
			/* Исходящее сообщение */
			message = new UserTextMessage(msg.toObject()["body"].toString(), Session::getInstance().getPhoto());
		}
		else
		{
			/* Входящее сообщение */
			message = new OpponentTextMessage(msg.toObject()["body"].toString(), this->photo);
		}

		userMessages << message;
	}

	for (auto &message : userMessages)
	{
		message->setDataToWidgets();
		emit messageLoaded(message,username);
	}
}

void DialogInfo::setConnections()
{
	// #TODO: Метод пуст!
	
}

void DialogInfo::setDataToWidgets()
{
	/* Отображение даты последнего сообщения */
	if (QDate::currentDate() == lastMessageDateTime.date())
	{
		ui.lastMessageDateTime->setTime(lastMessageDateTime.time());
		ui.lastMessageDateTime->setDisplayFormat("h:m");
	}
	else
	{
		ui.lastMessageDateTime->setDate(lastMessageDateTime.date());
		ui.lastMessageDateTime->setDisplayFormat("d MMM");
	}

	/* Отображение последнего сообщения диалога */
	if (out)
	{
		this->lastMessage.prepend ("Вы: ");
	}
	ui.lastMessage->setText(lastMessage);
}

DialogInfo & DialogInfo::operator=(const DialogInfo &other)
{
	this->userId = other.userId;
	this->messageId = other.messageId;
	this->title = other.title;
	this->lastMessage = other.lastMessage;
	this->username = other.username;
	this->lastMessageDateTime = other.lastMessageDateTime;
	this->out = other.out;

	return *this;
}

void DialogInfo::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) 
	{
		clicked = true;
	}
}

void DialogInfo::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && clicked) 
	{
		clicked = false;
		loadMessages();
	}
}
