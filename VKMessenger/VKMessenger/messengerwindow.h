#ifndef MESSENGERWINDOW_H
#define MESSENGERWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QPixmap>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QCloseEvent>
#include <QScrollBar>
#include "ui_messengerwindow.h"
#include "authorization.h"
#include "dialoginfo.h"
#include "session.h"
#include "dialogs.h"
#include "dialoginfo.h"

#define DATA_FILENAME "./Data/data.vkmd"

//gafk555@gmail.com
// #TODO: Кэшировать сообщения
// #TODO: Скорректировать механизм распознавания чата


class MessengerWindow : public QMainWindow
{
	Q_OBJECT

public:
	MessengerWindow(QWidget *parent = 0);
	~MessengerWindow();

signals:
	void userInfoLoaded();

private slots:
	void authorizationCompleted();
	void authorizationFailed();
	void loadDialogs();
	void messagesReceived(QWidget *scrollWidget, QString &username);
	void dialogsLoaded(QList<DialogInfo *> *userDialogs);
	void moveScrollBarToBotton(int min, int max);

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
	//QWidget *messagesScrollWidget;
};

#endif // MESSENGERWINDOW_H
