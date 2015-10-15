#include "authorization.h"

Authorization::Authorization(QObject *parent)
	: QObject(parent)
{
	browser = new QWebView;
	browser->resize(AUTH_WINDOW_WIDTH, AUTH_WINDOW_HEIGHT);

	setConnections();
}

Authorization::~Authorization()
{
	delete browser;
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
		QString accessToken = query.queryItemValue("access_token");
		QString expiresIn = query.queryItemValue("expires_in");
		QString userId = query.queryItemValue("user_id");
		emit authorizationCompleted(accessToken, userId, expiresIn);
	}
	else
	{
		QMessageBox::critical(browser, "Ошибка доступа", "Вы не предоставили приложению необходимые права доступа");
		emit authorizationFailed();
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
}
