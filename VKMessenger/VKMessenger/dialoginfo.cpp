#include "dialoginfo.h"

DialogInfo::DialogInfo(/*QWidget *parent, */unsigned int userId, unsigned int messageId, QString &title, QString &lastMessage, QDateTime &lastMessageDateTime, bool out) /*: QWidget(parent)*/
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
}

DialogInfo::~DialogInfo()
{
	delete dataReceiver;
}

void DialogInfo::opponentInfoReceived(const QByteArray &userInfo)
{
	/* Получаем информацию о пользователе */
	QJsonObject userDataObject = QJsonDocument::fromJson(userInfo).object();
	QJsonValue userDataValue = userDataObject.value("response");
	QJsonArray userDataArray = userDataValue.toArray();
	QString userName = userDataArray[0].toObject().value("first_name").toString() + " " + userDataArray[0].toObject().value("last_name").toString();
	QString userPhoto = userDataArray[0].toObject().value("photo_50").toString();
	ui.name->setText(userName);
	loadOpponentPhoto(userPhoto);
}

void DialogInfo::opponentPhotoLoaded(const QByteArray &userPhoto)
{
	QPixmap photo;
	if (!userPhoto.isEmpty() && photo.loadFromData(userPhoto))
	{
		ui.photo->setPixmap(photo);
	}
	else
	{
		// #TODO: Попытаться загрузить еще раз?
	}
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

		dataReceiver->sendRequest("users.get", parametres);
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
		dataReceiver->loadPhoto(QUrl(photoUrl));
	}
}

void DialogInfo::setConnections()
{
	connect(dataReceiver, SIGNAL(dataReceived(const QByteArray &)), this, SLOT(opponentInfoReceived(const QByteArray &)));
	connect(dataReceiver, SIGNAL(photoReceived(const QByteArray &)), this, SLOT(opponentPhotoLoaded(const QByteArray &)));
}

void DialogInfo::setDataToWidgets()
{
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

	if (out)
	{
		this->lastMessage.prepend ("Вы: ");
	}
	ui.lastMessage->setText(lastMessage);
	ui.lastMessageDateTime->setDateTime(lastMessageDateTime);
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
