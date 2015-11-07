#ifndef OPPONENTTEXTMESSAGE_H
#define OPPONENTTEXTMESSAGE_H

#include "ui_opponenttextmessage.h"
#include "abstractmessage.h"

class OpponentTextMessage : public AbstractMessage
{
	Q_OBJECT

public:
	OpponentTextMessage(QString &message, QByteArray &photo);
	OpponentTextMessage(const OpponentTextMessage &other);
	~OpponentTextMessage();

	virtual void setDataToWidgets();
	virtual OpponentTextMessage * clone() const;

private:
	Ui::OpponentTextMessage ui;
	QString message;
};

#endif // OPPONENTTEXTMESSAGE_H
