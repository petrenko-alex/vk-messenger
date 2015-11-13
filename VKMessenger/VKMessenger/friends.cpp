#include "friends.h"

Friends & Friends::getInstance()
{
	static Friends instance;
	return instance;
}

void Friends::loadFriends(QComboBox *list)
{
	QList<QPair<QString, QString> > parametres;
	parametres << QPair<QString, QString>("order", "hints");
	parametres << QPair<QString, QString>("fields", "photo_50");
	parametres << QPair<QString, QString>("name_case", "Nom");
	parametres << QPair<QString, QString>("count", QString::number (FRIENDS_NUMBER));
	parametres << QPair<QString, QString>("v", "5.40");
	parametres << QPair<QString, QString>("access_token", Session::getInstance().get("accessToken"));

	/* Посылаем запрос - получаем ответ */
	VKDataReceiver dataReceiver;
	QByteArray data = dataReceiver.loadData("friends.get", parametres);

	if (!data.isEmpty() && QJsonDocument::fromJson(data).object().value("response").isObject())
	{
		QJsonArray friendsArray = QJsonDocument::fromJson(data).object().value("response").toObject().value("items").toArray();

		int index = 0;
		for (auto i : friendsArray)
		{
			QPair<QString, QByteArray> tmpFriend;
			tmpFriend.first = i.toObject().value("first_name").toString() + " " + i.toObject().value("last_name").toString();

			QString photoStr = i.toObject().value("photo_50").toString();
			QByteArray photo = dataReceiver.loadPhoto(QUrl(photoStr));

			unsigned int id = i.toObject().value("id").toDouble();
			list->addItem(tmpFriend.first, id);

			QPixmap friendPhoto;
			if (!photo.isEmpty() && friendPhoto.loadFromData(photo))
			{
				tmpFriend.second = photo;
				list->setItemIcon(index, QIcon(friendPhoto));
			}

			++index;
			friends.insert(id, tmpFriend);
		}
	}
	else if (data.isEmpty() || QJsonDocument::fromJson(data).object().value("error").isObject())
	{
		QMessageBox::warning(0, "Ошибка загрузки", "Не удалось загрузить список друзей");
	}
}

QByteArray Friends::getPhoto(unsigned int id) const
{
	QByteArray tmp;
	if (friends.contains(id))
	{
		tmp = friends.value(id).second;
	}
	return tmp;
}

bool Friends::containsPhoto(unsigned int id) const
{
	return friends.contains(id) && !(friends.value(id).second.isNull());
}

Friends::Friends()
{

}
