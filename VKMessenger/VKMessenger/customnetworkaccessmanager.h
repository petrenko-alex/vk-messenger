#ifndef CUSTOMNETWORKACCESSMANAGER_H
#define CUSTOMNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager >
#include <QNetworkRequest>

class CustomNetworkAccessManager : public QNetworkAccessManager 
{
	Q_OBJECT

public:
	CustomNetworkAccessManager(QSsl::SslProtocol protocol, QSslSocket::PeerVerifyMode mode);

private:
	QSsl::SslProtocol protocol;
	QSslSocket::PeerVerifyMode mode;
protected:
	QNetworkReply * createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0);
};

#endif // CUSTOMNETWORKACCESSMANAGER_H
