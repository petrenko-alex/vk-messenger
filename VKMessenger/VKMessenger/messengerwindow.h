#ifndef MESSENGERWINDOW_H
#define MESSENGERWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_messengerwindow.h"
#include "authorization.h"
#include "dialoginfo.h"



class MessengerWindow : public QMainWindow
{
	Q_OBJECT

public:
	MessengerWindow(QWidget *parent = 0);
	~MessengerWindow();

private slots:
	void authorizationCompleted(const QString &accessToken, const QString &userId, const QString &expiresIn);
	void authorizationFailed();

private:
	void setConnections();

	Ui::MessengerWindowClass ui;

	/* Модуль авторизации */
	Authorization *authorization;

	QString accessToken;
	QString userId;
	QString expiresIn;
};

#endif // MESSENGERWINDOW_H
