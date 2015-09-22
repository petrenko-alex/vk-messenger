#include "authorization.h"

Authorization::Authorization(QObject *parent)
	: QObject(parent)
{

	browser = new QWebView;
	manager = new QNetworkAccessManager(this);
	browser->resize(700, 700);
	

	authorizationUrl.setUrl("https://api.vk.com/oauth/authorize");
	redirectUri.setUrl("https://api.vk.com/blank.html");

	QUrlQuery query;
	query.addQueryItem("client_id", QString::number(VK_APPLICATION_ID).toUtf8());
	query.addQueryItem("scope", "friends,photos,audio,video,docs,messages");
	query.addQueryItem("redirect_uri", redirectUri.toString());
	query.addQueryItem("display", "page");
	query.addQueryItem("response_type", "token");
	
	authorizationUrl.setQuery(query);


	browser->load(authorizationUrl);
	browser->show();
	
}

Authorization::~Authorization()
{
	delete browser;
}

