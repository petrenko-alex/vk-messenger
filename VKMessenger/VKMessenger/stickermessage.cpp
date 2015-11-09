#include "stickermessage.h"

StickerMessage::StickerMessage(const QByteArray &sticker, const QByteArray &photo)
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

void StickerMessage::setDataToWidgets(bool out)
{
	QPixmap stickerPixMap;
	QPixmap userPhoto;
	QByteArray tmpPhoto;

	/* Устанавливаем стикер */
	if (!this->sticker.isEmpty() && stickerPixMap.loadFromData(sticker))
	{
		ui.sticker->setPixmap(stickerPixMap);
	}

	/* Исходящее или входящее сообщение */
	if (out)
	{
		this->setLayoutDirection(Qt::LeftToRight);
		ui.frame->setLayoutDirection(Qt::RightToLeft);
		tmpPhoto = Session::getInstance().getPhoto();
	}
	else
	{
		this->setLayoutDirection(Qt::RightToLeft);
		ui.frame->setLayoutDirection(Qt::LeftToRight);
		tmpPhoto = photo;
	}

	/* Устанавливаем фото */
	if (!tmpPhoto.isEmpty() && userPhoto.loadFromData(tmpPhoto))
	{
		ui.photo->setPixmap(userPhoto);
	}
}

StickerMessage * StickerMessage::clone() const
{
	return (new StickerMessage(*this));
}