#ifndef VKDATARECEIVER_H
#define VKDATARECEIVER_H

#include <QObject>
#include <QByteArray>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>
#include <QIODevice>
#include <QUrlQuery>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QList>
#include <QPair>
#include <QTimer>
#include <QEventLoop>

#define  WAIT_FOR_ANSWER_TIME 10000
#define  LONG_POLL_ANSWER_TIME 30000
#define  STICKERS_PATH "./Application Resources/Stickers/"

class VKDataReceiver : public QObject
{
	Q_OBJECT

public:
	VKDataReceiver();
	~VKDataReceiver();

	QByteArray loadPhoto(const QUrl &photoUrl);
	QByteArray loadSticker(const QUrl &stickerUrl);
	QByteArray loadData(const QString &methodName, const QList<QPair<QString, QString> > &parametres);
	QByteArray longPollRequest(const QString &path, const QList<QPair<QString, QString> > &parametres);

};

#endif // VKDATARECEIVER_H
