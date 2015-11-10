#include "session.h"

Session & Session::getInstance()
{
	static Session session;
	return session;
}

QString Session::get(const QString &key) const
{
	return sessionData.contains(key) ? sessionData[key] : "";
}

void Session::add(const QString &key, const QString &value)
{
	sessionData[key] = value;
}

void Session::setPhoto(const QByteArray &photo)
{
	this->photo = photo;
}

QByteArray & Session::getPhoto()
{
	return photo;
}

void Session::setCurrentOpponent(const unsigned int id)
{
	this->currentOpponentId = id;
}

unsigned int Session::getCurrentOpponent()
{
	return this->currentOpponentId;
}

void Session::deleteSession()
{
	sessionData.clear();
	photo.clear();
	currentOpponentId = 0;
}

Session::Session()
{
}

QDataStream & operator<<(QDataStream &stream, const Session &session)
{
	QList<QString> keys = session.sessionData.keys();
	int elementsCount = keys.size();
	stream << elementsCount;

	for (int i = 0; i < elementsCount;++i)
	{
		stream << keys[i];
		QString value;
		value = session.sessionData.value(keys[i]);
		stream << value;
	}

	return stream;
}

QDataStream & operator>>(QDataStream &stream, Session &session)
{
	int elementsCount = 0;
	stream >> elementsCount;

	for (int i = 0; i < elementsCount; ++i)
	{
		QString key;
		stream >> key;
		QString value;
		stream >> value;
		Session::getInstance().add(key, value);
	}

	return stream;
}