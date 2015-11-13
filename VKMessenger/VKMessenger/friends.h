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

	void loadFriends(QComboBox *list);
	QByteArray getPhoto(unsigned int id) const;
	bool containsPhoto(unsigned int id) const;

private:
	Friends();
	Friends(const Friends &) = delete;
	Friends(const Friends &&) = delete;
	void operator=(const Friends &) = delete;
	void operator=(const Friends &&) = delete;

	QHash<unsigned int, QPair<QString, QByteArray> > friends;
};

#endif // FRIENDS_H
