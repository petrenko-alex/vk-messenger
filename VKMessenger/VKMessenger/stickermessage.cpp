#include "stickermessage.h"

StickerMessage::StickerMessage(QByteArray &sticker, QByteArray &photo)
	: AbstractMessage(photo)
{
	ui.setupUi(this);
	this->sticker = sticker;
}

StickerMessage::StickerMessage(const StickerMessage &other)
	: AbstractMessage(other)
{
	this->sticker = sticker;
}

StickerMessage::~StickerMessage()
{

}

void StickerMessage::setDataToWidgets()
{
	QPixmap stickerPixMap;
	QPixmap userPhoto;

	if (!this->sticker.isEmpty() && stickerPixMap.loadFromData(sticker))
	{
		ui.sticker->setPixmap(stickerPixMap);
	}

	if (!photo.isEmpty() && userPhoto.loadFromData(photo))
	{
		ui.photo->setPixmap(userPhoto);
	}
}

StickerMessage * StickerMessage::clone() const
{
	return (new StickerMessage(*this));
}