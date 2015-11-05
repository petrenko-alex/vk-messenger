#include "vkdatareceiver.h"

VKDataReceiver::VKDataReceiver()
{
}

VKDataReceiver::~VKDataReceiver()
{
}

QByteArray & VKDataReceiver::sendRequest(const QString &methodName, const QList<QPair<QString, QString> > &parametres)
{
	QByteArray data;

	if (!methodName.isEmpty() && !parametres.isEmpty())
	{
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
		QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
		QNetworkRequest request(apiRequestUrl);
		QNetworkReply *reply = networkManager->get(request);
		/* Ожидаем ответ */
		QEventLoop waitForAnswer;
		connect(networkManager, SIGNAL(finished(QNetworkReply*)), &waitForAnswer, SLOT(quit()));
		connect(networkManager, SIGNAL(finished(QNetworkReply*)), networkManager, SLOT(deleteLater()));
		QTimer::singleShot(WAIT_FOR_ANSWER_TIME, &waitForAnswer, SLOT(quit()));
		waitForAnswer.exec();
		/* Получаем ответ */
		data = reply->readAll();
		reply->deleteLater();
	}

	return data;
}

QByteArray & VKDataReceiver::loadPhoto(const QUrl &photoUrl)
{
	QByteArray photo;

	if (!photoUrl.isEmpty())
	{
		/* Посылаем запрос */
		QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
		QNetworkRequest request(photoUrl);
		QNetworkReply *reply = networkManager->get(request);
		/* Ожидаем ответ */
		QEventLoop waitForAnswer;
		connect(networkManager, SIGNAL(finished(QNetworkReply*)), &waitForAnswer, SLOT(quit()));
		connect(networkManager, SIGNAL(finished(QNetworkReply*)), networkManager, SLOT(deleteLater()));
		QTimer::singleShot(WAIT_FOR_ANSWER_TIME, &waitForAnswer, SLOT(quit()));
		waitForAnswer.exec();
		/* Получаем ответ */
		photo = reply->readAll();
		reply->deleteLater();
	}

	return photo;
}

