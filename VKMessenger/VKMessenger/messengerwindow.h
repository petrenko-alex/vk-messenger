#ifndef MESSENGERWINDOW_H
#define MESSENGERWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QPixmap>
#include <QComboBox>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QCloseEvent>
#include <QLayout>
#include <QBoxLayout>
#include <QScrollBar>
#include "ui_messengerwindow.h"
#include "authorization.h"
#include "dialoginfo.h"
#include "session.h"
#include "dialogs.h"
#include "dialoginfo.h"
#include "friends.h"

#define DATA_FILENAME "./Data/data.vkmd"

// #TODO: Строка поиска

class MessengerWindow : public QMainWindow
{
	Q_OBJECT

public:
	MessengerWindow(QWidget *parent = 0);
	~MessengerWindow();

signals:
	/* Информация о пользователе загружена */
	void userInfoLoaded();

	/* Разорвать соединение с Long Poll */
	void stopTracing();

	/* Отправить сообщение msg */
	void newMessage(QString &msg);

	/* Открыть новый диалог с пользователем userId */
	void newDialog(unsigned int userId);

private slots:
	/* Слот, вызвывающийся при получении сигнала об успешной авторизации */
	void authorizationCompleted();

	/* Слот, вызвывающийся при получении сигнала о неуспешной авторизации */
	void authorizationFailed();

	/* Первоначальная зугрузка диалогов - инициализация диалогов */
	void loadDialogs();

	/* Слот, вызывающийся при получении сигнала о том, что сообщения выбранного диалога загружены */
	void messagesReceived(QWidget *scrollWidget, QString &username);

	/* Слот, вызывающийся при получении сигнала о том, что первоначальный список диалогов загружен */
	void dialogsLoaded(QList<DialogInfo *> *userDialogs);

	/* Передвинуть скролл бар в самый низ */
	void moveScrollBarToBotton(int min, int max);

	/* Сменить позицию диалога dialog в списке диалогов */
	void changeDialogPosition(QWidget *dialog);

	/* Отправить сообщение по нажатию кнопки "Отправить" */
	void sendMessage();

	/* Показать список друзей по нажатию кнопки "+" */
	void showFriends();

	/* Выйти из программы и очистить данные авторизации по нажатию кнопки "Выйти" */
	void logout();

	/* Закрыть программы */
	void closeProgram();

	/* Открыть новый диалог по выбору друга из списка друзей */
	void newDialog(int user);

private:
	/* Фильтр событий */
	bool eventFilter(QObject *obj, QEvent *event);

	/* Сохранить данные сессии в файл */
	bool saveData();

	/* Загрузить данные сессии из файла */
	bool loadData();

	/* Установить соединения */
	void setConnections();

	/* Перегрузка события закрытия окна */
	void closeEvent(QCloseEvent *event);

	Ui::MessengerWindowClass ui;

	/* Модуль авторизации */
	Authorization *authorization;

	/* Модуль диалогов */
	Dialogs *userDialogs;

	/* Модуль получения данных с ВК */
	VKDataReceiver *dataReceiver;

	/* Виджеты отображения */
	QWidget *dialogsScrollWidget;
	QComboBox *friendList;
};

#endif // MESSENGERWINDOW_H
