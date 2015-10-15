#include "authorization.h"

Authorization::Authorization(QObject *parent)
	: QObject(parent)
{
	browser = new QWebView;
	networkManager = new QNetworkAccessManager(this);

	browser->resize(AUTH_WINDOW_WIDTH, AUTH_WINDOW_HEIGHT);

	loadAuthorizationPage();

	setConnections();
}

Authorization::~Authorization()
{
	delete browser;
	delete networkManager;
}

void Authorization::urlChanged(const QUrl &url)
{
	QString stringUrl = url.toString();

	if (stringUrl.isEmpty() || url.path() == authorizationUrl.path())
	{
		return;
	}

	stringUrl.replace('#', '?');
	QUrl changedUrl(stringUrl);
	QUrlQuery query(changedUrl);
	QString error = query.queryItemValue("error");

	if (error.isEmpty())
	{
		accessToken = query.queryItemValue("access_token");
		expiresIn = query.queryItemValue("expires_in");
		userId = query.queryItemValue("user_id");
		loadDialogs();
	}
	else
	{
		QMessageBox::critical(browser, "Ошибка доступа", "Вы не предоставили приложению необходимые права доступа");
		accessToken.clear();
		expiresIn.clear();
		userId.clear();
	}
	browser->close();
}

void Authorization::loadFinished(bool isSuccesful)
{
	QUrl browserUrl(browser->url());
	QUrlQuery query(browserUrl);

	if (!isSuccesful)
	{
		browser->close();
		QMessageBox::critical(browser, "Ошибка соединения", "Не удалось подключиться к серверу vk.com");
	}
	else if (browserUrl.path() == authorizationUrl.path())
	{
		browser->show();
	}
	else if (query.hasQueryItem("error") || browserUrl.path() == redirectUri.path())
	{
		browser->hide();
	}
	else
	{
		browser->show();
	}
}

void Authorization::getReply(QNetworkReply *reply)
{
	const QByteArray dialogsData = reply->readAll();

	QString test = reply->url().path();
	if (reply->url().path() == "/method/messages.getDialogs")
	{
		emit dialogsLoaded(dialogsData);
	}
	else
	{
		/* Ошибка */
	}
}

void Authorization::loadAuthorizationPage()
{
	authorizationUrl.setUrl("https://oauth.vk.com/authorize");
	redirectUri.setUrl("https://oauth.vk.com/blank.html");

	QUrlQuery query;
	query.addQueryItem("client_id", QString::number(VK_APPLICATION_ID).toLatin1());
	query.addQueryItem("scope", "friends,photos,audio,video,docs,messages");
	query.addQueryItem("redirect_uri", redirectUri.toString());
	query.addQueryItem("display", "popup");
	query.addQueryItem("response_type", "token");
	authorizationUrl.setQuery(query);

	browser->load(authorizationUrl);
}

void Authorization::setConnections()
{
	connect(browser, SIGNAL(urlChanged(const QUrl&)), this, SLOT(urlChanged(const QUrl&)));
	connect(browser, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
	connect(networkManager, SIGNAL(finished(QNetworkReply*)),this,SLOT(getReply (QNetworkReply*)));
}

void Authorization::loadDialogs()
{
	QUrl url("https://api.vk.com/method/messages.getDialogs");

	QUrlQuery query;
	query.addQueryItem("count", "100");
	query.addQueryItem("v", "5.37");
	query.addQueryItem("access_token", accessToken);
	url.setQuery(query);

	QNetworkRequest dialogsRequest(url);
	networkManager->get(dialogsRequest);
}
