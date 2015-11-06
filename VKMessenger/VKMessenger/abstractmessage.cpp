#include "abstractmessage.h"

AbstractMessage::AbstractMessage(QString &message, QByteArray &photo)
	: message(message), photo(photo)

{
	ui.setupUi(this);
}

AbstractMessage::~AbstractMessage()
{

}

