#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QUrl>
#include <QDataStream>
#include "vkdatareceiver.h"

class Session
{
public:
	Session();
	Session(const QString &userName, 
		    const QString &userId, 
			const QUrl	  &userPhotoURL,
		    const QString &accessToken, 
		    const QString &expiresIn);

	~Session();

	Session & operator=(const Session &other);

	QString getUserName();
	QString getUserId();
	QUrl getUserPhotoURL();
	QString getAccessToken();
	QString getExpiresIn();
	QStringList & getSessionData();
	friend QDataStream & operator<<(QDataStream &stream, const Session &session);
	friend QDataStream & operator>>(QDataStream &stream, Session &session);
	

private:
	QString userName;
	QString userId;
	QUrl userPhotoURL;	
	QString accessToken;
	QString expiresIn;
};

#endif // SESSION_H
