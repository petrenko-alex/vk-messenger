#include "usertextmessage.h"

UserTextMessage::UserTextMessage(QString &message, QByteArray &photo) 
	: AbstractMessage(photo)
{
	ui.setupUi(this);
	this->message = message;
}

UserTextMessage::UserTextMessage(const UserTextMessage &other) 
	: AbstractMessage(other)
{
	this->message = other.message;
}

UserTextMessage::~UserTextMessage()
{

}

void UserTextMessage::setDataToWidgets()
{
	ui.message->setText(message);

	QPixmap userPhoto;

	if (!photo.isEmpty() && userPhoto.loadFromData(photo))
	{
		ui.photo->setPixmap(userPhoto);
	}
}

UserTextMessage * UserTextMessage::clone() const
{
	return (new UserTextMessage(*this));
}
