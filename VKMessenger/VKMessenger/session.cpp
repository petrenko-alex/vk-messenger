#include "session.h"


Session::Session(const QString &userName, const QString &userId, const QUrl &userPhotoURL, const QString &accessToken, const QString &expiresIn)
{
	this->userName = userName;
	this->userId = userId;
	this->userPhotoURL = userPhotoURL;
	this->accessToken = accessToken;
	this->expiresIn = expiresIn;
}

Session::Session()
{
	this->userName = "";
	this->userId = "";
	this->userPhotoURL = QUrl("");
	this->accessToken = "";
	this->expiresIn = "";
}

Session::~Session()
{

}

Session & Session::operator=(const Session &other)
{
	this->userName = other.userName;
	this->userId = other.userId;
	this->userPhotoURL = other.userPhotoURL;
	this->accessToken = other.accessToken;
	this->expiresIn = other.expiresIn;

	return *this;
}

QString Session::getUserName()
{
	return this->userName;
}

QString Session::getUserId()
{
	return this->userId;
}

QUrl Session::getUserPhotoURL()
{
	return this->userPhotoURL;
}

QString Session::getAccessToken()
{
	return this->accessToken;
}

QString Session::getExpiresIn()
{
	return this->expiresIn;
}

QStringList & Session::getSessionData()
{
	QStringList sessionData;
	sessionData << this->userName
				<< this->userId
				<< this->userPhotoURL.toDisplayString()
				<< this->accessToken
				<< this->expiresIn;

	return sessionData;
}

QDataStream & operator<<(QDataStream &stream, const Session &session)
{
	QString userPhotUrl = session.userPhotoURL.toDisplayString();

	stream	<< session.userName
			<< session.userId
			<< userPhotUrl
			<< session.accessToken
			<< session.expiresIn;

	return stream;
}

QDataStream & operator>>(QDataStream &stream, Session &session)
{
	QString userPhotoUrl;

	stream	>> session.userName
			>> session.userId
			>> userPhotoUrl
			>> session.accessToken
			>> session.expiresIn;

	session.userPhotoURL = QUrl(userPhotoUrl);

	return stream;
}