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
#include <QTimer>
#include <QEventLoop>

#define  WAIT_FOR_ANSWER_TIME 10000

class VKDataReceiver : public QObject
{
	Q_OBJECT

public:
	VKDataReceiver();
	~VKDataReceiver();

	QByteArray & sendRequest(const QString &methodName, const QList<QPair<QString, QString> > &parametres);
	QByteArray & loadPhoto(const QUrl &photoUrl);

};

#endif // VKDATARECEIVER_H
