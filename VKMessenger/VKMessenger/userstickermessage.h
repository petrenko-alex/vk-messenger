#ifndef USERSTICKERMESSAGE_H
#define USERSTICKERMESSAGE_H

#include "ui_userstickermessage.h"
#include "abstractmessage.h"

class UserStickerMessage : public AbstractMessage
{
	Q_OBJECT

public:
	UserStickerMessage(QByteArray &sticker, QByteArray &photo);
	UserStickerMessage(const UserStickerMessage &other);
	~UserStickerMessage();

	virtual void setDataToWidgets();
	virtual UserStickerMessage * clone() const;

private:
	Ui::UserStickerMessage ui;
	QByteArray sticker;
};

#endif // USERSTICKERMESSAGE_H
