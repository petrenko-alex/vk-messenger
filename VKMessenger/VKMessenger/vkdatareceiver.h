#ifndef VKDATARECEIVER_H
#define VKDATARECEIVER_H

#include <QObject>
#include <QByteArray>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QList>
#include <QPair>

class VKDataReceiver : public QObject
{
	Q_OBJECT

signals:
	void dataReceived(const QByteArray &data);

public:
	VKDataReceiver();
	~VKDataReceiver();

	void sendRequest(const QString &methodName, const QList<QPair<QString, QString> > &parametres, const QString &accessToken);

private:
	QNetworkAccessManager *networkManager;
	QString methodName;

private slots:
	void getReply(QNetworkReply *reply);
};

#endif // VKDATARECEIVER_H
