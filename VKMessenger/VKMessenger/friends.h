#ifndef FRIENDS_H
#define FRIENDS_H

#include <QObject>
#include <QComboBox>
#include <QMessageBox>
#include <QHash>
#include "session.h"
#include "vkdatareceiver.h"

#define FRIENDS_NUMBER 50

class Friends : public QObject
{
	Q_OBJECT

public:
	/* Получить объект класса */
	static Friends & getInstance();

	/* Загрузить список друзей */
	void loadFriends(QComboBox *list);

	/* Получить фото по id пользователя */
	QByteArray getPhoto(unsigned int id) const;

	/* Проверить, имеется ли фото пользователя с id */
	bool containsPhoto(unsigned int id) const;

private:
	Friends();
	Friends(const Friends &) = delete;
	Friends(const Friends &&) = delete;
	void operator=(const Friends &) = delete;
	void operator=(const Friends &&) = delete;

	/* Информация о друзьях - id, имя и фото */
	QHash<unsigned int, QPair<QString, QByteArray> > friends;
};

#endif // FRIENDS_H
