#include "authorization.h"

Authorization::Authorization(QObject *parent)
	: QObject(parent)
{
	browser = new QWebView;

	browser->resize(700, 700);



	authorizationUrl.setUrl("https://oauth.vk.com/authorize");
	redirectUri.setUrl("https://api.vk.com/blank.html");

	QUrlQuery query;
	query.addQueryItem("client_id", QString::number(VK_APPLICATION_ID).toLatin1());
	query.addQueryItem("scope", "friends,photos,audio,video,docs,messages");
	query.addQueryItem("redirect_uri", redirectUri.toString());
	query.addQueryItem("display", "popup");
	query.addQueryItem("response_type", "token");
	
	authorizationUrl.setQuery(query);
	

	browser->load(authorizationUrl);
	browser->show();
	
}

Authorization::~Authorization()
{
	delete browser;
}
