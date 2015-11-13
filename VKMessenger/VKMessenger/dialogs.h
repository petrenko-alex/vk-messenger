#ifndef DIALOGS_H
#define DIALOGS_H

#include <QObject>
#include <QPair>
#include <QSound>
#include <QJsonDocument>
#include <QMessageBox>
#include "session.h"
#include "vkdatareceiver.h"
#include "dialoginfo.h"
#include "vklongpoll.h"

#define DIALOGS_COUNT 20
#define NOTIFICATION_SOUND_PATH "./Application Resources/Sounds/new_message.wav"

class Dialogs : public QObject
{
	Q_OBJECT

signals:
	/* Сигнал - изменить позицию диалога widget в списке диалогов */
	void changeDialogPosition(QWidget *widget);

	/* Сигнал - диалоги загружены */
	void dialogsLoaded(QList<DialogInfo *> *userDialogs);

	/* Сигнал - сообщения загружены */
	void messagesLoaded(QWidget *scrollWidget, QString &username);

	/* Сигнал - можно закрывать программу - соединение с Long Poll разорвно */
	void canExit();

public:
	Dialogs();
	~Dialogs();

	/* Первоначальная загрузка диалогов - инициализация */
	void loadDialogs();

private slots:
	/* Слот, вызывающийся по сигналу о том, что сообщения диалога были загружены */
	void messagesReceived(QWidget *scrollWidget, QString &username);

	/* Слот, вызывающийся по сигналу о том, что было получено сообщение */
	void addMessage(MessageType type,const QString &fromId, const QString &text);

	/* Слот, вызывающийся по сигналу о том, что требуется разрыв соединения с Long Poll */
	void stopTracing();

	/* Слот, вызывающийся по сигналу о том, что соединение с Long Poll разорвано */
	void tracingStopped();

	/* Слот, вызывающийся по сигналу о том, что требуется отправка сообщения */
	void newMessage(QString &msg);

	/* Слот, вызывающийся по сигналу о том, что требуется открытие нового диалога */
	void newDialog(unsigned int userId);

	/* Слот, вызывающийся по сигналу о том, что сообщение было отправлено */
	void messageWasSent(QWidget *dialog);

	/* Добавить диалог по id userId */
	bool newDialogById(unsigned int userId);

private:
	/* Установить соединения */
	void setConnections();

	/* Получить count диалогов от ВК */
	bool getDialogs(unsigned int count);

	/* Распарсить полученных от ВК диалоги */
	void parseDialogs(const QByteArray &userDialogsData);

	/* Проверить, является ли чатом диалог с id id */
	bool isChat(const QString &id);

	/* Модуль получения данных с ВК */
	VKDataReceiver *dataReceiver;

	/* Модуль соединения с Long Poll */
	VKLongPoll *longPollConnection;

	/* Список диалогов пользователя */
	QList<DialogInfo *> userDialogs;
};

#endif // DIALOGS_H
