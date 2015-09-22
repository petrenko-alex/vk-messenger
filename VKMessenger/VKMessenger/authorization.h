#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QApplication>
#include <QObject>
#include <QtWebKit>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QWebView>
#include <QUrl>
#include <QNetworkAccessManager>

#define VK_APPLICATION_ID 5078976

class Authorization : public QObject
{
	Q_OBJECT

public:
	Authorization(QObject *parent);
	~Authorization();

private:
	QWebView *browser;
	QUrl authorizationUrl;
	QUrl redirectUri;
};

#endif // AUTHORIZATION_H
