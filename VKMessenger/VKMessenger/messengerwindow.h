#ifndef MESSENGERWINDOW_H
#define MESSENGERWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QPixmap>
#include "ui_messengerwindow.h"
#include "authorization.h"
#include "dialoginfo.h"
#include "session.h"

//gafk555@gmail.com

class MessengerWindow : public QMainWindow
{
	Q_OBJECT

public:
	MessengerWindow(QWidget *parent = 0);
	~MessengerWindow();

private slots:
	void authorizationCompleted(Session receivedSession);
	void authorizationFailed();
	void userPhotoLoaded(const QByteArray &data);

private:
	void setConnections();

	Ui::MessengerWindowClass ui;

	/* Модуль авторизации */
	Authorization *authorization;
	Session *currentSession;

	QString accessToken;
	QString userId;
	QString expiresIn;

	VKDataReceiver *dataReceiver;
};

#endif // MESSENGERWINDOW_H
