#include "opponenttextmessage.h"

OpponentTextMessage::OpponentTextMessage(QString &message, QByteArray &photo) 
	: AbstractMessage(message,photo)
{
	ui.setupUi(this);
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
