#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include <QWidget>
#include "ui_abstractmessage.h"

#define MIN_HEIGHT 86

class AbstractMessage : public QWidget
{
	Q_OBJECT

public:
	AbstractMessage(QString &message, QByteArray &photo);
	AbstractMessage(const AbstractMessage &other);
	virtual ~AbstractMessage();

	virtual void setDataToWidgets() = 0;
	virtual AbstractMessage * clone() const = 0;

protected:
	QByteArray photo;
	QString message;

private:
	Ui::AbstractMessage ui;
};

#endif // ABSTRACTMESSAGE_H
