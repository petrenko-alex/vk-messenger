#include "opponenttextmessage.h"

OpponentTextMessage::OpponentTextMessage(QString &message, QByteArray &photo) 
	: AbstractMessage(photo)
{
	ui.setupUi(this);
	this->message = message;
}

OpponentTextMessage::OpponentTextMessage(const OpponentTextMessage &other) 
	: AbstractMessage(other)
{
	this->message = other.message;
}

OpponentTextMessage::~OpponentTextMessage()
{

}

void OpponentTextMessage::setDataToWidgets()
{
	ui.message->setText(message);

	QPixmap userPhoto;

	if (!photo.isEmpty() && userPhoto.loadFromData(photo))
	{
		ui.photo->setPixmap(userPhoto);
	}
}

OpponentTextMessage * OpponentTextMessage::clone() const
{
	return (new OpponentTextMessage(*this));
}
