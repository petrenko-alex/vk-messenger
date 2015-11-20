#include "dialoginfo.h"

DialogInfo::DialogInfo(DialogType type,unsigned int id, QString &title, QString &lastMessage, QDateTime &lastMessageDateTime, bool out)
{
	ui.setupUi(this);
	ui.dialogInfo->installEventFilter(this);
	ui.lastMessage->installEventFilter(this);
	ui.lastMessageDateTime->installEventFilter(this);
	ui.line_2->installEventFilter(this);
	ui.name->installEventFilter(this);
	ui.photo->installEventFilter(this);

	dataReceiver = new VKDataReceiver;
	messagesScrollWidget = new QWidget;
	messagesScrollWidget->setLayout(new QVBoxLayout);

	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->setMinimumSize(WIDTH, HEIGHT);

	this->dialogType = type;
	this->id = id;
	this->name = title;
	this->lastMessage = lastMessage;
	this->lastMessageDateTime = lastMessageDateTime;
	this->out = out;

	setDataToWidgets();
	clicked = false;
	initialized = false;
	clickBlock = false;
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
			QString userName = userDataArray.at(0).toObject().value("first_name").toString() + " " + userDataArray.at(0).toObject().value("last_name").toString();
			QString userPhoto = userDataArray.at(0).toObject().value("photo_50").toString();

			ui.name->setText(userName);
			this->name = userName;
			loadOpponentPhoto(userPhoto);
		}
		else
		{
			qDebug() << "Данные собеседника \"" + this->name + "\" не загружены";
		}
		
	}
	else
	{
		/* Имя группы */
		ui.name->setText(name);
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
			qDebug() << "Фото собеседника \"" + this->name + "\" не загружено";
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

	emit messagesLoaded(messagesScrollWidget, name);
	initialized = true;
}

void DialogInfo::addMessage(MessageType type, const QString &fromId, const QString &text)
{
	AbstractMessage *message;
	if (type == MessageType::TEXT_MESSAGE)
	{
		message = new TextMessage(text, photo);

	}
	else if (type == MessageType::STICKER_MESSAGE)
	{
		QUrl stickerUrl("http://vk.com/images/stickers/" + text + "/128b.png");
		QByteArray sticker = dataReceiver->loadSticker(stickerUrl);
		message = new StickerMessage(sticker, photo);
	}
	userMessages.push_front (message);
	message->setDataToWidgets(false);
	messagesScrollWidget->layout()->addWidget (message);
	paintFrameRed();
}

QString DialogInfo::getId() const
{
	return QString::number(this->id);
}

QString DialogInfo::getUserName() const
{
	return this->name;
}

bool DialogInfo::isInitialized() const
{
	return this->initialized;
}

void DialogInfo::setLastMessage(const QString &text)
{
	ui.lastMessage->setText(text);
	ui.lastMessageDateTime->setTime(QTime::currentTime());
	ui.lastMessageDateTime->setDisplayFormat("H:mm");
}

void DialogInfo::parseMessages(const QByteArray &messages)
{
	QByteArray tmpPhoto;
	QJsonObject dialogMessagessObject = QJsonDocument::fromJson(messages).object();
	QJsonArray dialogMessagesArray = dialogMessagessObject.value("response").toObject()["items"].toArray();

	for (auto msg : dialogMessagesArray)
	{
		AbstractMessage *message = nullptr;
		QString messageAttachments = "";
		bool out = msg.toObject()["out"].toInt();

		/* Если чат - загружаем фото реального отправителя */
		if (dialogType == DialogType::CHAT)
		{
			tmpPhoto = loadPhotoByUserId(msg.toObject()["user_id"].toDouble());
		}
		else
		{
			tmpPhoto = this->photo;
		}

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

					message = new StickerMessage(sticker, tmpPhoto);
				}
				else
				{
					messageAttachments += a.toObject()["type"].toString() + ", ";
				}
			}
			messageAttachments.prepend("Вложения: ");
			messageAttachments.remove(messageAttachments.size() - 2, 2);
		}
		
		/* Если есть пересланные сообщения */
		if (msg.toObject().keys().contains("fwd_messages"))
		{
			messageAttachments += "\nПересланные сообщения";
		}


		if (message == nullptr)
		{
			QString messageText = msg.toObject()["body"].toString();
			if (! messageText.isEmpty())
			{
				messageAttachments.prepend("\n");
			}

			message = new TextMessage(messageText + messageAttachments, tmpPhoto);
		}

		userMessages << message;
		message->setDataToWidgets(out);
	}
}

void DialogInfo::paintFrameRed()
{
	if (Session::getInstance().getCurrentOpponent() != id)
	{
		this->setStyleSheet("QWidget#dialogInfo { border: 1px solid red; border-radius: 10px;} QWidget#dialogInfo:hover{ border: 2px solid black; border-radius: 10px;}");
	}
}

QWidget * DialogInfo::getMessagesWidget() const
{
	return this->messagesScrollWidget;
}

void DialogInfo::sendMessage(QString &msg)
{
	/* Формируем параметры запроса */
	QList<QPair<QString, QString> > parametres;
	if (dialogType == DialogType::PERSONAL)
	{
		parametres << QPair<QString, QString>("user_id", QString::number(id));
	}
	else
	{
		parametres << QPair<QString, QString>("chat_id", QString::number(id));
	}
	parametres << QPair<QString, QString>("message", msg);
	parametres << QPair<QString, QString>("v", "5.40");
	parametres << QPair<QString, QString>("access_token", Session::getInstance().get("accessToken"));

	/* Посылаем запрос, получаем данные */
	QByteArray response = dataReceiver->loadData("messages.send", parametres);

	if (! response.isEmpty() && QJsonDocument::fromJson(response).object().value("response").isDouble())
	{
		AbstractMessage *message = new TextMessage(msg, Session::getInstance().getPhoto());
		userMessages.push_front(message);
		message->setDataToWidgets(true);
		messagesScrollWidget->layout()->addWidget(message);
		setLastMessage(msg);
		emit messageWasSent(this);
	}
	else if (response.isEmpty() || QJsonDocument::fromJson(response).object().value("error").isObject())
	{
		QMessageBox::warning(this, "Ошибка отправки", "Не удалось отправить сообщение.");
	}
}

bool DialogInfo::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		return QWidget::eventFilter(obj, event);
	}
	return false;
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
	this->lastMessage = other.lastMessage;
	this->name = other.name;
	this->lastMessageDateTime = other.lastMessageDateTime;
	this->out = other.out;

	return *this;
}

void DialogInfo::paintFrameWhite()
{
	this->setStyleSheet("QWidget#dialogInfo { border: 1px solid white; border-radius: 10px;} QWidget#dialogInfo:hover{ border: 2px solid black; border-radius: 10px;}");
}

void DialogInfo::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && ! clickBlock) 
	{
		emit loadingStarted();
		paintFrameWhite();
		Session::getInstance().setCurrentOpponent(id);
		clicked = false;
		if (!initialized)
		{
			clickBlock = true;
			loadMessages();
			clickBlock = false;
		}
		else
		{
			emit messagesLoaded(messagesScrollWidget, name);
		}
	}
}

QByteArray DialogInfo::loadPhotoByUserId(unsigned int userId)
{
	/* Поиск фото в памяти */
	if (Friends::getInstance().containsPhoto(userId))
	{
		return Friends::getInstance().getPhoto(userId);
	}

	/* Если в памяти нет - загружаем с ВК */
	QList<QPair<QString, QString> > parametres;
	parametres << QPair<QString, QString>("user_ids", QString::number(userId));
	parametres << QPair<QString, QString>("fields", "photo_50");
	parametres << QPair<QString, QString>("v", "5.37");
	parametres << QPair<QString, QString>("access_token", Session::getInstance().get("accessToken"));

	QByteArray userInfo = dataReceiver->loadData("users.get", parametres);

	if (!userInfo.isEmpty())
	{
		QJsonObject doc = QJsonDocument::fromJson(userInfo).object();

		if (doc.value("response").isArray())
		{
			QJsonObject userDataValue = doc.value("response").toArray().at(0).toObject ();
			QString userPhoto = userDataValue.value("photo_50").toString();

			return dataReceiver->loadPhoto(QUrl(userPhoto));
		}
	}
	return QByteArray();
}
