#ifndef USERSTICKERMESSAGE_H
#define USERSTICKERMESSAGE_H

#include "ui_stickermessage.h"
#include "abstractmessage.h"

class StickerMessage : public AbstractMessage
{
	Q_OBJECT

public:
	StickerMessage(const QByteArray &sticker, const QByteArray &photo);
	StickerMessage(const StickerMessage &other);
	~StickerMessage();

	/* Установить данные в виджет */
	virtual void setDataToWidgets(bool out);
	
	/* Склонировать объект класса */
	virtual StickerMessage * clone() const;

private:
	Ui::UserStickerMessage ui;
	QByteArray sticker;
};

#endif // USERSTICKERMESSAGE_H
