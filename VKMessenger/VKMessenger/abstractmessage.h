#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include <QWidget>
#include "ui_abstractmessage.h"

class AbstractMessage : public QWidget
{
	Q_OBJECT

public:
	AbstractMessage(QString &message, QByteArray &photo);
	virtual ~AbstractMessage();

protected:
	QByteArray photo;
	QString message;
	virtual void setDataToWidgets() = 0;

private:
	Ui::AbstractMessage ui;
};

#endif // ABSTRACTMESSAGE_H
