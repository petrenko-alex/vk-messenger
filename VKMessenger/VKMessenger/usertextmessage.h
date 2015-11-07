#ifndef USERTEXTMESSAGE_H
#define USERTEXTMESSAGE_H

#include "ui_usertextmessage.h"
#include "abstractmessage.h"

class UserTextMessage : public AbstractMessage
{
	Q_OBJECT

public:
	UserTextMessage(QString &message, QByteArray &photo);
	UserTextMessage(const UserTextMessage &other);
	~UserTextMessage();

	virtual void setDataToWidgets();
	virtual UserTextMessage * clone() const;

private:
	Ui::UserTextMessage ui;
	QString message;
};

#endif // USERTEXTMESSAGE_H
