#include "customnetworkaccessmanager.h"



CustomNetworkAccessManager::CustomNetworkAccessManager(QSsl::SslProtocol protocol, QSslSocket::PeerVerifyMode mode)
{
	this->protocol = protocol;
	this->mode = mode;
}

QNetworkReply * CustomNetworkAccessManager::createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData /*= 0*/)
{
	QSslConfiguration config = req.sslConfiguration();
	config.setPeerVerifyMode(mode);
	config.setProtocol(protocol);
	QNetworkRequest request(req);
	request.setSslConfiguration(config);
	return QNetworkAccessManager::createRequest(op, request, outgoingData);
}

