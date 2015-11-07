#ifndef USERSTICKERMESSAGE_H
#define USERSTICKERMESSAGE_H

#include "ui_stickermessage.h"
#include "abstractmessage.h"

class StickerMessage : public AbstractMessage
{
	Q_OBJECT

public:
	StickerMessage(QByteArray &sticker, QByteArray &photo);
	StickerMessage(const StickerMessage &other);
	~StickerMessage();

	virtual void setDataToWidgets();
	virtual StickerMessage * clone() const;

private:
	Ui::UserStickerMessage ui;
	QByteArray sticker;
};

#endif // USERSTICKERMESSAGE_H
