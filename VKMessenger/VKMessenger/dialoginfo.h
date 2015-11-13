#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QWidget>
#include <QDateTime>
#include <QUrl>
#include <QMouseEvent>
#include <QJsonDocument>
#include <QMessageBox>
#include "ui_dialoginfo.h"
#include "session.h"
#include <windows.h>
#include "vkdatareceiver.h"
#include "abstractmessage.h"
#include "textmessage.h"
#include "stickermessage.h"
#include "friends.h"

#define WIDTH  260
#define HEIGHT 100
#define MESSAGES_COUNT 100
#define GROUP_AVATAR_PATH "./Application Resources/group_avatar.png"

enum DialogType { PERSONAL, CHAT };

class DialogInfo : public QWidget
{
	Q_OBJECT

public:
	DialogInfo(	DialogType type, unsigned int id,
				QString &title,QString &lastMessage,
				QDateTime &lastMessageDateTime, bool out);
	~DialogInfo();

	DialogInfo & operator=(const DialogInfo &other);

	/* Загрузить данные о собеседнике */
	void loadOpponentInfo();

	/* Загрузить фото собеседника */
	void loadOpponentPhoto(QString photoUrl);

	/* Загрузить сообщения диалога */
	void loadMessages();

	/* Добавить новое сообщение к диалогу (входящее) */
	void addMessage(MessageType type,const QString &fromId, const QString &text);

	/* Отправить сообщение собеседнику */
	void sendMessage(QString &msg);

	/* Получить id собеседника */
	QString getId() const;

	/* Получить имя собеседника */
	QString getUserName() const;

	/* Проверить, инициализирован ли диалог - были ли загружены его сообщения */
	bool isInitialized() const;

	/* Установить последнее сообщение диалога в виджет */
	void setLastMessage(const QString &text);

	/* Окрасить рамку виджета в красный цвет - признак наличия нового сообщения в диалоге */
	void paintFrameRed();

	/* Получить виджет сообщений */
	QWidget * getMessagesWidget() const;

signals:
	/* Сигнал - сообщения диалога загружены */
	void messagesLoaded(QWidget *scrollWidget, QString &username);

	/* Сигнал - сообщение отправлено */
	void messageWasSent(QWidget *dialog);

private:
	/* Фильтр событий */
	bool eventFilter(QObject *obj, QEvent *event);

	/* Установить данные в виджет диалога */
	void setDataToWidgets();

	/* Распарсить сообщения диалога */
	void parseMessages(const QByteArray &messages);

	/* Окрасить рамку виджета в белый цвет - нормальное состояние */
	void paintFrameWhite();

	/* Обработать клик по виджету диалога */
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

	/* Загрузить фото собеседника по id (для диалога типа CHAT) */
	QByteArray loadPhotoByUserId(unsigned int userId);

	Ui::DialogInfo ui;

	/* Данные диалога */
	bool out;
	QString name;
	unsigned int id;
	QByteArray photo;
	QString lastMessage;
	DialogType dialogType;
	QDateTime lastMessageDateTime;

	/* Флаги, управляющие поведением виджета диалога */
	bool clicked;
	bool clickBlock;
	bool initialized;

	/* Модуль получения данных с ВК */
	VKDataReceiver *dataReceiver;

	/* Список сообщений диалога */
	QList<AbstractMessage *> userMessages;

	/* Виджет сообщение диалога */
	QWidget *messagesScrollWidget;
};

#endif // DIALOGINFO_H
