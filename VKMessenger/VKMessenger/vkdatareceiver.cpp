#include "vkdatareceiver.h"

VKDataReceiver::VKDataReceiver()
{
	networkManager = new QNetworkAccessManager(this);
	this->methodName = "";

	connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getReply(QNetworkReply*)));
}

VKDataReceiver::~VKDataReceiver()
{
	delete networkManager;
	networkManager = NULL;
}

void VKDataReceiver::sendRequest(const QString &methodName,const QList<QPair<QString,QString> > &parametres)
{
	if (!methodName.isEmpty() && !parametres.isEmpty())
	{
		this->methodName = methodName;

		/* Создаем URL запроса на основе переданного имени метода API */
		QString stringUrl = "https://api.vk.com/method/" + methodName;
		QUrl apiRequestUrl(stringUrl);

		/* Добавляем параметры запроса в URL */
		QUrlQuery query;
		for (auto i : parametres)
		{
			query.addQueryItem(i.first, i.second);
		}
		apiRequestUrl.setQuery(query);

		/* Посылаем запрос */
		QNetworkRequest request(apiRequestUrl);
		networkManager->get(request);
	}
}

void VKDataReceiver::loadPhoto(const QUrl &photoUrl)
{
	if (!photoUrl.isEmpty())
	{
		this->photoUrl = photoUrl;
		QNetworkRequest request(photoUrl);
		networkManager->get(request);
	}
}

void VKDataReceiver::getReply(QNetworkReply *reply)
{
	const QByteArray data = reply->readAll();

	if (reply->url().path() == ("/method/" + methodName))
	{
		emit dataReceived(data);
	}
	else if (reply->url().toDisplayString() == photoUrl.toDisplayString())
	{
		emit photoReceived(data);
	}
	else
	{
		// #TODO: Породить исключение.
	}
}
