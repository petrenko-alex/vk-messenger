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

#define  WAIT_FOR_ANSWER_TIME 30000
#define  STICKERS_PATH "./Application Resources/Stickers/"

class VKDataReceiver : public QObject
{
	Q_OBJECT

public:
	VKDataReceiver();
	~VKDataReceiver();

	/* Получить фото по url */
	QByteArray loadPhoto(const QUrl &photoUrl);

	/* Получить стикер по url */
	QByteArray loadSticker(const QUrl &stickerUrl);

	/* Получить данные метода API methodName с параметрами parametres */
	QByteArray loadData(const QString &methodName, const QList<QPair<QString, QString> > &parametres);

	/* Получить данные для подключения к Long Poll */
	QByteArray longPollRequest(const QString &serverPath, const QList<QPair<QString, QString> > &parametres);

private:
	/* Запрос к ВК по url с параметрами parametres */
	QByteArray request(QUrl &url, const QList<QPair<QString, QString> > &parametres);

};

#endif // VKDATARECEIVER_H
