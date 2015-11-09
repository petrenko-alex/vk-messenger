#include "abstractmessage.h"

AbstractMessage::AbstractMessage(const QByteArray &photo)
	:  photo(photo)

{
	ui.setupUi(this);
}

AbstractMessage::AbstractMessage(const AbstractMessage &other)
{
	this->photo = other.photo;
}

AbstractMessage::~AbstractMessage()
{

}

