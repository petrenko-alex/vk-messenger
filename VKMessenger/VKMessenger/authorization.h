#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QApplication>
#include <QObject>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtWebKit>
#include <QList>
#include <QPair>
#include <QtNetwork>
#include <QUrl>
#include <QWebView>
#include "vkdatareceiver.h"
#include "session.h"

#define VK_APPLICATION_ID 5078976
#define AUTH_WINDOW_WIDTH 640
#define AUTH_WINDOW_HEIGHT 420

class Authorization : public QObject
{
	Q_OBJECT

public:
	Authorization(QObject *parent);
	~Authorization();

	/* Метод, загружающий страницу авторизации Вконтакте */
	void loadAuthorizationPage();

signals:
	/* Сигнал об успешной авторизации */
	void authorizationCompleted(Session &currentSession);
	/* Сигнал о неуспешной авторизации */
	void authorizationFailed();

private slots:
	/* Слот, вызывающийся при перенаправлении браузера browser */
	void urlChanged(const QUrl &url);
	/* Слот, вызывающийся при окончании загрузки браузером browser страницы */
	void loadFinished(bool isSuccesful);
	/* Слот, вызывающийся при успешном получении данных об авторизовавшемся пользователе */
	void userInfoReceived(const QByteArray &userInfo);

private:
	/* Соединение сигналов и слотов */
	void setConnections();
	/* Запрос на получение данных об авторизовавшемся пользователе */
	void loadUserInfo();

	/* Поля класса */
	QWebView *browser;		
	VKDataReceiver *dataReceiver;
	QUrl authorizationUrl;
	QUrl redirectUri;
	QString accessToken;
	QString expiresIn;
	QString userId;
};

#endif // AUTHORIZATION_H
