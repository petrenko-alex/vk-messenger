#include "usertextmessage.h"

TextMessage::TextMessage(QString &message, QByteArray &photo) 
	: AbstractMessage(photo)
{
	ui.setupUi(this);
	this->message = message;
}

TextMessage::TextMessage(const TextMessage &other) 
	: AbstractMessage(other)
{
	this->message = other.message;
}

TextMessage::~TextMessage()
{

}

void TextMessage::setDataToWidgets(bool out)
{
	QPixmap userPhoto;
	QByteArray tmpPhoto;

	/* Устанавливаем текст */
	ui.message->setText(message);

	/* Исходящее или входящее сообщение */
	if (out)
	{
		this->setLayoutDirection(Qt::LeftToRight);
		tmpPhoto = Session::getInstance().getPhoto();
	}
	else
	{
		this->setLayoutDirection(Qt::RightToLeft);
		tmpPhoto = photo;
	}

	/* Устанавливаем фото */
	if (!tmpPhoto.isEmpty() && userPhoto.loadFromData(tmpPhoto))
	{
		ui.photo->setPixmap(userPhoto);
	}
}

TextMessage * TextMessage::clone() const
{
	return (new TextMessage(*this));
}
