#ifndef MESSENGERWINDOW_H
#define MESSENGERWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QPixmap>
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

#define DATA_FILENAME "./Data/data.vkmd"

// #TODO: Добавить загрузку фото собеседников чата
// #TODO: Если нажать одновременно несколько диалогов!
// #TODO: Создание диалога - чата по сигналу из Long Poll
// #TODO: Отправка сообщения
// #TODO: Вызов сообщений диалога по нажатию на все части виджета диалога
// #TODO: Кнопка плюсик


class MessengerWindow : public QMainWindow
{
	Q_OBJECT

public:
	MessengerWindow(QWidget *parent = 0);
	~MessengerWindow();

signals:
	void userInfoLoaded();
	void stopTracing();

private slots:
	void authorizationCompleted();
	void authorizationFailed();
	void loadDialogs();
	void messagesReceived(QWidget *scrollWidget, QString &username);
	void dialogsLoaded(QList<DialogInfo *> *userDialogs);
	void moveScrollBarToBotton(int min, int max);
	void changeDialogPosition(QWidget *dialog);
	void sendMessage();
	void logout();
	void closeProgram();

private:
	bool saveData();
	bool loadData();
	void setConnections();
	void closeEvent(QCloseEvent *event);

	Ui::MessengerWindowClass ui;
	Authorization *authorization;
	Dialogs *userDialogs;
	VKDataReceiver *dataReceiver;
	QWidget *dialogsScrollWidget;
};

#endif // MESSENGERWINDOW_H
