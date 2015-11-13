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
	void userInfoLoaded();
	void stopTracing();
	void newMessage(QString &msg);
	void newDialog(unsigned int userId);

private slots:
	void authorizationCompleted();
	void authorizationFailed();
	void loadDialogs();
	void messagesReceived(QWidget *scrollWidget, QString &username);
	void dialogsLoaded(QList<DialogInfo *> *userDialogs);
	void moveScrollBarToBotton(int min, int max);
	void changeDialogPosition(QWidget *dialog);
	void sendMessage();
	void showFriends();
	void logout();
	void closeProgram();
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
