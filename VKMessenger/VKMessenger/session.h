#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <QStringList>
#include <QUrl>

class Session
{

public:
	Session(const QString &userName, 
		    const QString &userId, 
		    const QUrl &userPhoto, 
		    const QString &accessToken, 
		    const QString &expiresIn);

	~Session();

	QString getUserName();
	QString getUserId();
	QUrl getUserPhoto();
	QString getAccessToken();
	QString getExpiresIn();
	QStringList & getSessionData();

private:
	QString userName;
	QString userId;
	QUrl userPhoto;
	QString accessToken;
	QString expiresIn;
};

#endif // SESSION_H
