#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QApplication>
#include <QObject>
#include <QMessageBox>
#include <QtWebKit>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QUrl>
#include <QWebView>
#include <QNetworkAccessManager>

#define VK_APPLICATION_ID 5078976
#define AUTH_WINDOW_WIDTH 640
#define AUTH_WINDOW_HEIGHT 420

class Authorization : public QObject
{
	Q_OBJECT

public:
	Authorization(QObject *parent);
	~Authorization();

private slots:
	void urlChanged(const QUrl &url);
	void loadFinished(bool isSuccesful);
	void getReply(QNetworkReply *reply);

private:
	void loadAuthorizationPage();
	void setConnections();

	QString accessToken;
	QString expiresIn;
	QString userId;
	

	QWebView *browser;
	QNetworkAccessManager *networkManager;
	QUrl authorizationUrl;
	QUrl redirectUri;
};

#endif // AUTHORIZATION_H
