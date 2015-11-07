#include "abstractmessage.h"

AbstractMessage::AbstractMessage(QString &message, QByteArray &photo)
	: message(message), photo(photo)

{
	ui.setupUi(this);
}

AbstractMessage::AbstractMessage(const AbstractMessage &other)
{
	this->message = other.message;
	this->photo = other.photo;
}

AbstractMessage::~AbstractMessage()
{

}

