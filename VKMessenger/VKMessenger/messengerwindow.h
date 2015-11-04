#ifndef MESSENGERWINDOW_H
#define MESSENGERWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QPixmap>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QCloseEvent>
#include "ui_messengerwindow.h"
#include "authorization.h"
#include "dialoginfo.h"
#include "session.h"
#include "dialogs.h"
#include "dialoginfo.h"

#define DATA_FILENAME "./Data/data.vkmd"

//gafk555@gmail.com

class MessengerWindow : public QMainWindow
{
	Q_OBJECT

public:
	MessengerWindow(QWidget *parent = 0);
	~MessengerWindow();

signals:
	void userInfoLoaded();

private slots:
	void authorizationCompleted(Session receivedSession);
	void authorizationFailed();
	void userPhotoLoaded(const QByteArray &data);
	void loadDialogs();
	void dialogReceived(DialogInfo *dialogInfo);
	bool saveData();
	bool loadData();

private:
	void setConnections();
	void closeEvent(QCloseEvent *event);

	Ui::MessengerWindowClass ui;
	Authorization *authorization;
	Dialogs *userDialogs;
	VKDataReceiver *dataReceiver;
	Session currentSession;

	QWidget *dialogsScrollWidget;
};

#endif // MESSENGERWINDOW_H
