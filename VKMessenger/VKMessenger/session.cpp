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