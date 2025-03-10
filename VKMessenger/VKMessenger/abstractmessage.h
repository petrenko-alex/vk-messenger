#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include <QWidget>
#include "ui_abstractmessage.h"
#include "session.h"

#define MIN_HEIGHT 86

enum MessageType
{
	TEXT_MESSAGE,
	STICKER_MESSAGE
};

class AbstractMessage : public QWidget
{
	Q_OBJECT

public:
	AbstractMessage(const QByteArray &photo);
	AbstractMessage(const AbstractMessage &other);
	virtual ~AbstractMessage();

	/* ���������� ������ � ������ */
	virtual void setDataToWidgets(bool out) = 0;

	/* ������������ ������ ������ */
	virtual AbstractMessage * clone() const = 0;

protected:
	QByteArray photo;

private:
	Ui::AbstractMessage ui;
};

#endif // ABSTRACTMESSAGE_H
