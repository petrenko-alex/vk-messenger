#ifndef VKLONGPOLL_H
#define VKLONGPOLL_H

#include <QObject>
#include <QDebug>
#include "session.h"
#include "vkdatareceiver.h"

class VKLongPoll : public QObject
{
	Q_OBJECT

public:
	VKLongPoll(QObject *parent);
	~VKLongPoll();

	/* Получить данные для подключения к Long Poll серверу */
	void getLongPollServer();
	/* Подключиться к Long Poll и получать новые события */
	void trace();

signals:
	/* Сигнал - сообщение получено */
	void messageReceived(const QString &fromId, const QString &text);

private:
	/* Данные для подключения к Long Poll серверу */
	QString ts;
	QString pts;
	QString key;
	QString server;
	/* Тип полученного события */
	enum EventType
	{
		NEW_MESSAGE = 4
	};
};

#endif // VKLONGPOLL_H
