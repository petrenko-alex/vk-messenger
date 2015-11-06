#ifndef USERTEXTMESSAGE_H
#define USERTEXTMESSAGE_H

#include "ui_usertextmessage.h"
#include "abstractmessage.h"

class UserTextMessage : public AbstractMessage
{
	Q_OBJECT

public:
	UserTextMessage(QString &message, QByteArray &photo);
	~UserTextMessage();

	virtual void setDataToWidgets();

private:
	Ui::UserTextMessage ui;
};

#endif // USERTEXTMESSAGE_H
