#ifndef VKLONGPOLL_H
#define VKLONGPOLL_H

#include <QObject>
#include <QDebug>
#include "session.h"
#include "vkdatareceiver.h"
#include "abstractmessage.h"

class VKLongPoll : public QObject
{
	Q_OBJECT

public:
	VKLongPoll(QObject *parent);
	~VKLongPoll();

	/* Получить данные для подключения к Long Poll серверу */
	void getLongPollServer();

	/* Подключиться к Long Poll и получать новые события */
	void startTracing();

	/* Остановить работу с Long Poll сервером */
	void stopTracing();

signals:
	/* Сигнал - сообщение получено */
	void messageReceived(MessageType type, const QString &fromId, const QString &text);

	/* Сигнал - соединение с Long Poll разорвано */
	void tracingStopped();

private:
	/* Получить строку с типами прикреплений полученного сообщения */
	QString getAttachmentsString(QJsonObject &attachments);

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

	/* Флаг разрыва соединение - остановки бесконечного цикла */
	bool stopConnection;
};

#endif // VKLONGPOLL_H
