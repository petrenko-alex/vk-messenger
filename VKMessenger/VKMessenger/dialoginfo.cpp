#include "dialoginfo.h"

DialogInfo::DialogInfo(DialogType type,unsigned int id, unsigned int messageId, QString &title, QString &lastMessage, QDateTime &lastMessageDateTime, bool out)
{
	ui.setupUi(this);
	dataReceiver = new VKDataReceiver;
	messagesScrollWidget = new QWidget;
	messagesScrollWidget->setLayout(new QVBoxLayout);
	setConnections();

	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->setMinimumSize(WIDTH, HEIGHT);

	this->dialogType = type;
	this->id = id;
	this->messageId = messageId;
	this->title = title;
	this->lastMessage = lastMessage;
	this->lastMessageDateTime = lastMessageDateTime;
	this->out = out;

	setDataToWidgets();
	clicked = false;
	initialized = false;
}

DialogInfo::~DialogInfo()
{
	delete dataReceiver;
	delete messagesScrollWidget;
}

void DialogInfo::loadOpponentInfo()
{
	if (dialogType == DialogType::PERSONAL)
	{
		/* Загружаем информацию о собеседнике */
		QList<QPair<QString, QString> > parametres;
		parametres << QPair<QString, QString>("user_ids", QString::number(id));
		parametres << QPair<QString, QString>("fields", "photo_50");
		parametres << QPair<QString, QString>("name_case", "Nom");
		parametres << QPair<QString, QString>("v", "5.37");
		parametres << QPair<QString, QString>("access_token", Session::getInstance().get("accessToken"));

		QByteArray userInfo = dataReceiver->loadData("users.get", parametres);
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
		/* Фото группы */
		ui.photo->setPixmap(QPixmap(GROUP_AVATAR_PATH));
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
	/* Формируем запрос на получение сообщений */
	QList<QPair<QString, QString> > parametres;
	parametres << QPair<QString, QString>("count", QString::number(MESSAGES_COUNT));
	if (dialogType == DialogType::PERSONAL)
	{
		parametres << QPair<QString, QString>("user_id", QString::number(id));
	}
	else
	{
		parametres << QPair<QString, QString>("chat_id", QString::number(id));
	}
	parametres << QPair<QString, QString>("v", "5.37");
	parametres << QPair<QString, QString>("access_token", Session::getInstance().get("accessToken"));
	/* Посылаем запрос, получаем данные */
	QByteArray messages = dataReceiver->loadData("messages.getHistory", parametres);

	if (!messages.isEmpty())
	{
		parseMessages(messages);
	}
	
	auto it = userMessages.cend();
	auto end = userMessages.cbegin();
	while (it != end)
	{
		--it;
		messagesScrollWidget->layout()->addWidget(*it);
	}

	emit messagesLoaded(messagesScrollWidget, username);
	initialized = true;
}


void DialogInfo::addMessage(const QString &fromId, const QString &text)
{
	bool out;
	AbstractMessage *message = new TextMessage(text, photo);
	userMessages.push_front (message);
	message->setDataToWidgets(out);
	messagesScrollWidget->layout()->addWidget (message);
	paintFrameRed();
}

QString DialogInfo::getId() const
{
	return QString::number(this->id);
}

void DialogInfo::setLastMessage(const QString &text)
{
	ui.lastMessage->setText(text);
	ui.lastMessageDateTime->setTime(QTime::currentTime());
	ui.lastMessageDateTime->setDisplayFormat("H:mm");
}

void DialogInfo::parseMessages(const QByteArray &messages)
{
	QJsonObject dialogMessagessObject = QJsonDocument::fromJson(messages).object();
	QJsonArray dialogMessagesArray = dialogMessagessObject.value("response").toObject()["items"].toArray();

	for (auto msg : dialogMessagesArray)
	{
		AbstractMessage *message = nullptr;
		QString messageAttachments = "Вложения: ";
		bool out = msg.toObject()["out"].toInt();

		if (msg.toObject()["body"].toString().isEmpty())
		{
			/* Если есть вложения */
			if (msg.toObject().keys().contains("attachments"))
			{
				QJsonArray attachments = msg.toObject()["attachments"].toArray();

				for (auto a : attachments)
				{
					if (a.toObject()["type"] == "sticker")
					{
						QString stickerUrl = a.toObject()["sticker"].toObject()["photo_128"].toString();
						QByteArray sticker = dataReceiver->loadSticker(stickerUrl);

						message = new StickerMessage(sticker, this->photo);
					}
					else
					{
						messageAttachments += a.toObject()["type"].toString() + ", ";
					}
				}
				messageAttachments.remove(messageAttachments.size() - 2,2);
			}
		}
		else
		{
			message = new TextMessage(msg.toObject()["body"].toString(), this->photo);
		}

		if (message == nullptr)
		{
			message = new TextMessage(messageAttachments, this->photo);
		}

		userMessages << message;
		message->setDataToWidgets(out);
	}
}

void DialogInfo::paintFrameRed()
{
	if (Session::getInstance().getCurrentOpponent() != id)
	{
		this->setStyleSheet("QWidget#dialogInfo {border: 1px solid red;border-radius: 10px;}");
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
		ui.lastMessageDateTime->setDisplayFormat("H:mm");
	}
	else
	{
		ui.lastMessageDateTime->setDate(lastMessageDateTime.date());
		ui.lastMessageDateTime->setDisplayFormat("d MMM.");
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
	this->id = other.id;
	this->messageId = other.messageId;
	this->title = other.title;
	this->lastMessage = other.lastMessage;
	this->username = other.username;
	this->lastMessageDateTime = other.lastMessageDateTime;
	this->out = other.out;

	return *this;
}

void DialogInfo::paintFrameWhite()
{
	this->setStyleSheet("QWidget#dialogInfo {border: 1px solid white;border-radius: 10px;}");
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
		paintFrameWhite();
		Session::getInstance().setCurrentOpponent(id);
		clicked = false;
		if (!initialized)
		{
			loadMessages();
		}
		else
		{
			emit messagesLoaded(messagesScrollWidget, username);
		}
	}
}
