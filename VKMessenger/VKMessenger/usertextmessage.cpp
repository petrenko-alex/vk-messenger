#include "usertextmessage.h"

UserTextMessage::UserTextMessage(QString &message, QByteArray &photo) 
	: AbstractMessage(message,photo)
{
	ui.setupUi(this);
}

UserTextMessage::UserTextMessage(const UserTextMessage &other) 
	: AbstractMessage(other)
{

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
