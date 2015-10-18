#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QUrl>
#include <QImage>
#include "vkdatareceiver.h"

class Session
{
public:
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
	

private:
	QString userName;
	QString userId;
	QUrl userPhotoURL;	
	QString accessToken;
	QString expiresIn;
};

#endif // SESSION_H
