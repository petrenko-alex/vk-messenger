#include "userstickermessage.h"

UserStickerMessage::UserStickerMessage(QByteArray &sticker, QByteArray &photo)
	: AbstractMessage(photo)
{
	ui.setupUi(this);
	this->sticker = sticker;
}

UserStickerMessage::UserStickerMessage(const UserStickerMessage &other)
	: AbstractMessage(other)
{
	this->sticker = sticker;
}

UserStickerMessage::~UserStickerMessage()
{

}

void UserStickerMessage::setDataToWidgets()
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

UserStickerMessage * UserStickerMessage::clone() const
{
	return (new UserStickerMessage(*this));
}