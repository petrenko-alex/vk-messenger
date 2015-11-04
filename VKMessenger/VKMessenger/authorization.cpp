#include "authorization.h"

Authorization::Authorization(QObject *parent)
	: QObject(parent)
{
	browser = new QWebView;
	dataReceiver = new VKDataReceiver;
	browser->resize(AUTH_WINDOW_WIDTH, AUTH_WINDOW_HEIGHT);

	setConnections();
}

Authorization::~Authorization()
{
	delete browser;
	delete dataReceiver;
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
		loadUserInfo();
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

void Authorization::userInfoReceived(const QByteArray &userInfo)
{
	/* Получаем информацию о пользователе */
	QJsonObject userDataObject = QJsonDocument::fromJson(userInfo).object();
	QJsonValue userDataValue = userDataObject.value("response");
	QJsonArray userDataArray = userDataValue.toArray();
	QString userName = userDataArray[0].toObject().value("first_name").toString() + " " + userDataArray[0].toObject().value("last_name").toString();
	QString userPhoto = userDataArray[0].toObject().value("photo_50").toString();
	/* Сигнал об успешной авторизации */
	Session::getInstance().add("userName", userName);
	Session::getInstance().add("userId", userId);
	Session::getInstance().add("userPhoto", userPhoto);
	Session::getInstance().add("accessToken", accessToken);
	Session::getInstance().add("expiresIn", expiresIn);
	emit authorizationCompleted();
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
	connect(dataReceiver, SIGNAL(dataReceived(const QByteArray &)), this, SLOT(userInfoReceived(const QByteArray &)));
}

void Authorization::loadUserInfo()
{
	QList<QPair<QString, QString> > parametres;
	parametres << QPair<QString,QString>("fields", "photo_50");
	parametres << QPair<QString, QString>("name_case", "Nom");
	parametres << QPair<QString, QString>("v", "5.37");
	parametres << QPair<QString, QString>("access_token", accessToken);

	dataReceiver->sendRequest("users.get", parametres);
}
