#include "session.h"


Session::Session(const QString &userName, const QString &userId, const QUrl &userPhoto, const QString &accessToken, const QString &expiresIn)
{
	this->userName = userName;
	this->userId = userId;
	this->userPhoto = userPhoto;
	this->accessToken = accessToken;
	this->expiresIn = expiresIn;
}

Session::~Session()
{

}

Session & Session::operator=(const Session &other)
{
	this->userName = other.userName;
	this->userId = other.userId;
	this->userPhoto = other.userPhoto;
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

QUrl Session::getUserPhoto()
{
	return this->userPhoto;
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
				<< this->userPhoto.toDisplayString()
				<< this->accessToken
				<< this->expiresIn;

	return sessionData;
}

